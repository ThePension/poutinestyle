#include "StatePlayGame.h"

StatePlayGame::StatePlayGame(GameManager* game)
{
    this->gameManager = game;
    
    gameManager->getRenderWindow()->setMouseCursorVisible(false);
    gameManager->getRenderWindow()->setMouseCursorGrabbed(true); // The mouse can't leave the window

    oldMouseX = sf::Mouse::getPosition().x;
    sf::Mouse::setPosition(sf::Vector2i(gameManager->getWindowWidth() / 2, gameManager->getWindowHeight() / 2));

    blockWidth = gameManager->getWindowWidth() / mapSize;
    blockHeight = gameManager->getWindowHeight() / mapSize;

    map = new char*[mapSize];
    for (int i = 0; i < mapSize; i++)
    {
        map[i] = new char[mapSize];
        for (int j = 0; j < mapSize; j++)
        {
            map[i][j] = '0';
        }
    }
    
	parseMap2D();

    wallTextures = sf::Texture();    
    wallTextures.loadFromFile("../PoutineStyle/pics/textures.png");

    // Load cursor texture
    imgAimCursor.loadFromFile("Cursor/cursorAim3.png");
}
sf::Vector2f StatePlayGame::rotateVectorMatrix(sf::Vector2f v, double a) {
    // Rotation matrix (used to rotate vector by an angle)
    // [cosa  -sina]
    // [sina   cosa]
    sf::Vector2f resVec = sf::Vector2f();
    resVec.x = v.x * cos(a) - v.y * sin(a);
    resVec.y = v.x * sin(a) + v.y * cos(a);

    // Need a unit vector --> Divide vector's components by the length of the vector
    /*double vecLen = sqrt(pow(resVec.x, 2) + pow(resVec.y, 2));
    resVec.x /= vecLen;
    resVec.y /= vecLen;*/
    return resVec;
}
StatePlayGame::~StatePlayGame()
{
    for (int x = 0; x < gameManager->getWindowWidth(); x++) {
        for (int y = 0; y < gameManager->getWindowHeight(); y++) {
            if (entityMap[x][y] != nullptr) {
                entities.remove(entityMap[x][y]);
                delete entityMap[x][y]; entityMap[x][y] = nullptr;
            }
        }
    }
}
void StatePlayGame::handleInput(double deltatime)
{
    sf::Event event;

    while (gameManager->getRenderWindow()->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            gameManager->getRenderWindow()->close();
        }

        if (event.type == sf::Event::MouseMoved && gameManager->getRenderWindow()->hasFocus())
        {
            float speedFactor = 5;
            int mouseX = event.mouseMove.x;

            if (mouseX == 0)
            {
                mouseX = gameManager->getWindowWidth() - 1;
                sf::Mouse::setPosition(sf::Vector2i(gameManager->getWindowWidth() / 2 + mouseX, sf::Mouse::getPosition().y));
            }
            else if (mouseX >= gameManager->getWindowWidth() - 1)
            {
                mouseX = 0;
                sf::Mouse::setPosition(sf::Vector2i(gameManager->getWindowWidth()/2, sf::Mouse::getPosition().y));
            }
            else if (oldMouseX > mouseX) // go to left | 0 --- mouseX -- < -- oldMouseX --- maxWidth
            {
                player.direction = rotateVectorMatrix(player.direction, -speedFactor * deltatime); // Rotate the player direction
                player.planeVec = rotateVectorMatrix(player.planeVec, -speedFactor * deltatime); // Rotate plane direction
            }
            else if (oldMouseX < mouseX)  // go to right | 0 --- oldMouseX -- < -- mouseX --- maxWidth
            {
                player.direction = rotateVectorMatrix(player.direction, speedFactor * deltatime); // Rotate the player direction
                player.planeVec = rotateVectorMatrix(player.planeVec, speedFactor * deltatime); // Rotate plane direction
            }
            
            oldMouseX = mouseX;
        }

        if (event.type == sf::Event::KeyPressed)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) isMapDisplayed = !isMapDisplayed; // Toggle map display
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) player.reload();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) wPressed = true;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) aPressed = true;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) sPressed = true;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) dPressed = true;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) movingSpeed = 5;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) InteractedEntity = getInteractedEntity();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) pause();
        }

        if (event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::A) aPressed = false;
            if (event.key.code == sf::Keyboard::D) dPressed = false;
            if (event.key.code == sf::Keyboard::W) wPressed = false;
            if (event.key.code == sf::Keyboard::S) sPressed = false;
            if (event.key.code == sf::Keyboard::LShift) movingSpeed = 3;
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            if (typeid(*player.getCurrentWeapon()).name() == typeid(Knife).name()) {
                player.shoot(player.direction);
                Entity* entity = getInteractedEntity();
                if (entity != nullptr) {
                    if (typeid(*entity).name() == typeid(Ennemy).name()) {
                        Ennemy* ennemy = static_cast<Ennemy*>(entity);
                        ennemy->decreaseHP(player.getCurrentWeapon()->getDamage());
                        // Remove the ennemy if his HP are under 1
                        if (ennemy->getHP() <= 0) {
                            ennemy->setIsDying();
                        }
                    }
                }
            }
            else{
                Bullet* bullet = player.shoot(player.direction);
                if (bullet != nullptr) {
                    entities.push_back(bullet);
                }
            }
        }
    }
}

void StatePlayGame::pause()
{
    if (!isGamePaused)
    {
        isGamePaused = true;
        reset();
        StatePauseMenu* statePauseMenu = new StatePauseMenu(this->gameManager);
        this->gameManager->getRenderWindow()->setMouseCursorVisible(true);
        this->gameManager->pushState(statePauseMenu);
    }
}

void StatePlayGame::resume()
{
    if (isGamePaused)
    {
        isGamePaused = false;
        this->gameManager->getRenderWindow()->setMouseCursorVisible(false);
    }
}

void StatePlayGame::reset()
{
    aPressed = false;
    sPressed = false;
    dPressed = false;
    wPressed = false;
    movingSpeed = 3;
}

void StatePlayGame::update(float deltaTime)
{
    handleInput(deltaTime);

    // Player controls
    sf::Vector2f newPlayerPos;

    if (aPressed)
    {
        newPlayerPos = sf::Vector2f(player.position.x - player.planeVec.x * movingSpeed * deltaTime, player.position.y - player.planeVec.y * movingSpeed * deltaTime);
        updatePlayerPosition(newPlayerPos);
    }

    if (dPressed)
    {
        newPlayerPos = sf::Vector2f(player.position.x + player.planeVec.x * movingSpeed * deltaTime, player.position.y + player.planeVec.y * movingSpeed * deltaTime);
        updatePlayerPosition(newPlayerPos);
    }

    if (wPressed)
    {
        newPlayerPos = sf::Vector2f(player.position.x + player.direction.x * movingSpeed * deltaTime, player.position.y + player.direction.y * movingSpeed * deltaTime);
        updatePlayerPosition(newPlayerPos);
    }

    if (sPressed)
    {
        newPlayerPos = sf::Vector2f(player.position.x - player.direction.x * movingSpeed * deltaTime, player.position.y - player.direction.y * movingSpeed * deltaTime);
        updatePlayerPosition(newPlayerPos);
    }

    draw(deltaTime);
}

void StatePlayGame::updatePlayerPosition(sf::Vector2f newPos)
{
    int newPosMapY, newPosMapX;

    newPosMapY = newPos.x;
    newPosMapX = newPos.y;

    if (   map[newPosMapX][newPosMapY] != '1'
        && map[newPosMapX][newPosMapY] != 'D'
        && map[newPosMapX][newPosMapY] != 'V'
        && map[newPosMapX][newPosMapY] != 'W'
        && map[newPosMapX][newPosMapY] != 'X'
        && map[newPosMapX][newPosMapY] != 'Y'
        && map[newPosMapX][newPosMapY] != 'Z'
        )
    {
        // Move the player position (backward) depending on player direction
        player.position = newPos;
    }
}

void StatePlayGame::draw(double dt)
{
    if(isMapDisplayed) drawMap2D();
    else
    {
        renderingWalls(dt);
        renderingEntities(dt);
        hud();
    }
}

void StatePlayGame::drawMap2D()
{
    sf::RectangleShape block;
    block.setSize(sf::Vector2f(blockWidth, blockHeight));
    block.setOutlineThickness(1);
    block.setOutlineColor(sf::Color::Black);

    sf::CircleShape player_circle;
    player_circle.setRadius(5);
    player_circle.setPosition(sf::Vector2f(player.position.x * (blockWidth) - player_circle.getRadius(), player.position.y * (blockHeight - 1) - player_circle.getRadius() / 2.0));
    player_circle.setFillColor(sf::Color::Green);

    for (int i = 0; i < mapSize; i++)
    {
        for (int j = 0; j < mapSize; j++)
        {
            block.setPosition(j * blockWidth, i * blockHeight);

            if (map[i][j] == '1') // needs a fastest way to test if there's more cases. [ O(n^2) ]
            {
                block.setFillColor(sf::Color::Red);
            }
            else if (map[i][j] == '0')
            {
                block.setFillColor(sf::Color::Black);
            }
            else {
                block.setFillColor(sf::Color::Blue);
            }

            gameManager->getRenderWindow()->draw(block);
        }
    }
    gameManager->getRenderWindow()->draw(player_circle);

    // Draw player direction vector
    sf::Vertex playerDirLine[] =
    {
        sf::Vertex(sf::Vector2f(player_circle.getPosition().x + player_circle.getRadius(), player_circle.getPosition().y + player_circle.getRadius())),
        sf::Vertex(sf::Vector2f(player_circle.getPosition().x + player_circle.getRadius() + 16 * player.direction.x, player_circle.getPosition().y + player_circle.getRadius() + 16 * player.direction.y))
    };

    gameManager->getRenderWindow()->draw(playerDirLine, 2, sf::Lines);
}

void StatePlayGame::renderingWalls(double dt)
{
#pragma region Rendering Walls
    yOffset = 0; // Used to create the illusion of a taller player
    // Number of rays (vertical lines drawn on the screen) --> Must be a multiple of 66
    int w = gameManager->getWindowWidth();
    sf::VertexArray lines(sf::Lines, 2 * w); // Must be bigger if we want to draw floors and ceilings
    
    for (int x = 0; x < w; x++) { // FOV of 66 degrees --> 66 rays
        int wallTextureNum = 3; // Need to be set depending on wall type (char)
        // Cell where the player is standing
        sf::Vector2i playerMapPos = sf::Vector2i(int(player.position.x), int(player.position.y));

        // Vector representing the direction of the actual ray
        double cameraX = double(2.f * x) / double(w) - 1;

        sf::Vector2f rayDir = player.direction + sf::Vector2f(player.planeVec.x * cameraX, player.planeVec.y * cameraX);
        double rayDirLen = std::sqrt(pow(rayDir.x, 2) + pow(rayDir.y, 2));

        // Fisheye effect
        // double deltaDistX = (rayDir.x == 0) ? 1e30 : abs(rayDirLen / rayDir.x);
        // double deltaDistY = (rayDir.y == 0) ? 1e30 : abs(rayDirLen / rayDir.y);

        double deltaDistX = (rayDir.x == 0) ? 0 : abs(1 / rayDir.x); // RayDir is a unit vector, length = 1
        double deltaDistY = (rayDir.y == 0) ? 0 : abs(1 / rayDir.y);

        double sideDistX, sideDistY;

        int stepX, stepY;
        bool wallHit = false, isWallHitHorizontal = false;

        if (rayDir.x < 0) {
            stepX = -1;
            sideDistX = ((player.position.x) - double(playerMapPos.x)) * deltaDistX;
        }
        else {
            stepX = 1;
            sideDistX = (double(playerMapPos.x) + 1.f - (player.position.x)) * deltaDistX;
        }
        if (rayDir.y < 0) {
            stepY = -1;
            sideDistY = ((player.position.y) - double(playerMapPos.y)) * deltaDistY;
        }
        else {
            stepY = 1;
            sideDistY = (double(playerMapPos.y) + 1.f - (player.position.y)) * deltaDistY;
        }
        int ceilingPixel = 0; // position of ceiling pixel on the screen
        int groundPixel = gameManager->getWindowHeight(); // position of ground pixel on the screen
        sf::Color color1 = sf::Color(100, 100, 100), color2 = sf::Color(150, 150, 150);
        sf::Color floorColor = ((playerMapPos.x % 2 == 0 && playerMapPos.y % 2 == 0) || (playerMapPos.x % 2 == 1 && playerMapPos.y % 2 == 1)) ? color1 : color2;
        double perpWallDist;
        // DDA algorithm
        while (wallHit == false) {
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX; // Always the same
                playerMapPos.x += stepX;
                isWallHitHorizontal = true;
            }
            else {
                sideDistY += deltaDistY;
                playerMapPos.y += stepY;
                isWallHitHorizontal = false;
            }

            if (map[playerMapPos.y][playerMapPos.x] == '1') wallHit = true;
            else if (map[playerMapPos.y][playerMapPos.x] == 'D') {
                wallHit = true;
                wallTextureNum = 8;
            }
            else if (map[playerMapPos.y][playerMapPos.x] == 'V') {
                wallHit = true;
                wallTextureNum = 9;
            }
            else if (map[playerMapPos.y][playerMapPos.x] == 'W') {
                wallHit = true;
                wallTextureNum = 10;
            }
            else if (map[playerMapPos.y][playerMapPos.x] == 'X') {
                wallHit = true;
                wallTextureNum = 11;
            }
            else if (map[playerMapPos.y][playerMapPos.x] == 'Y') {
                wallHit = true;
                wallTextureNum = 12;
            }
            else if (map[playerMapPos.y][playerMapPos.x] == 'Z') {
                wallHit = true;
                wallTextureNum = 13;
            }
            else { //if (map[playerMapPos.y][playerMapPos.x] == 'E' || map[playerMapPos.y][playerMapPos.x] == 'C' || map[playerMapPos.y][playerMapPos.x] == 'L') {
                if (entityMap[playerMapPos.x][playerMapPos.y] != nullptr) {
                    entityMap[playerMapPos.x][playerMapPos.y]->setToDraw(true);
                }
            }
            if (isWallHitHorizontal) perpWallDist = sideDistX - deltaDistX;
            else perpWallDist = sideDistY - deltaDistY;
            // Floor
            double wallHeight = int(gameManager->getWindowHeight() / perpWallDist);
            // Add floor
            lines.append(sf::Vertex(sf::Vector2f((float)x, (float)groundPixel + yOffset), floorColor));
            groundPixel = int(wallHeight * 0.495 + double(gameManager->getWindowHeight()) * 0.5f);
            lines.append(sf::Vertex(sf::Vector2f((float)x, (float)groundPixel + yOffset), floorColor));
            
            if (floorColor == color1) floorColor = color2;
            else floorColor = color1;
        }

        sf::Color wallColor;

        if (isWallHitHorizontal) wallColor = sf::Color::White;
        else wallColor = sf::Color(126, 126, 126);

        int lineHeight = int(gameManager->getWindowHeight() / perpWallDist);

        int drawStart = -lineHeight / 2 + gameManager->getWindowHeight() / 2;
        int drawEnd = lineHeight / 2 + gameManager->getWindowHeight() / 2;

        // Texture stuff
        sf::Vector2i texture_coords(
            wallTextureNum * textureSize,
            0 // For the moment, all textures are on the same line (y coord) in textures.png file
        );

        // Calculate where the wall was hit
        float wallX;
        if (isWallHitHorizontal) wallX = (player.position.y) + perpWallDist * rayDir.y;
        else wallX = (player.position.x) + perpWallDist * rayDir.x;
        wallX -= floor(wallX);

        // Get x coordinate on the wall texture
        int texX = int(wallX * float(textureSize));
        if ((isWallHitHorizontal && rayDir.x > 0) || (!isWallHitHorizontal && rayDir.y < 0))
            texX = textureSize - texX - 1;

        texture_coords.x += texX;

        // Adding vertical lines in ArrayVertex, and set the coordinates of the texture to use
        // x * 2 are all the first points of the lines (top ones) (more info there : https://www.sfml-dev.org/tutorials/2.5/graphics-vertex-array.php)
        lines[x * 2].position = sf::Vector2f((float)x, (float)drawStart + yOffset);
        lines[x * 2].color = wallColor;
        lines[x * 2].texCoords = sf::Vector2f((float)texture_coords.x, (float)texture_coords.y + 1);
        // x * 2 + 1 are all the seconds points of the lines (bottom ones)
        lines[x * 2 + 1].position = sf::Vector2f((float)x, (float)drawEnd + yOffset);
        lines[x * 2 + 1].color = wallColor;
        lines[x * 2 + 1].texCoords = sf::Vector2f((float)texture_coords.x, (float)(texture_coords.y + textureSize - 1));

        ZBuffer[x] = perpWallDist; // Needed for entities rendering
    }

    // Draw walls with textures
    gameManager->getRenderWindow()->draw(lines, &wallTextures);
    lines.clear();
    lines.resize(2 * w);

#pragma endregion
}

void StatePlayGame::renderingEntities(double dt) {
#pragma region Entity Interaction Management
    if (InteractedEntity != nullptr) {
        if (typeid(*InteractedEntity).name() == typeid(Chest).name()) { // Chest interaction
            Chest* chest = static_cast<Chest*>(InteractedEntity);
            chest->setIsOpening();
            InteractedEntity = nullptr;
        }
        else if (typeid(*InteractedEntity).name() == typeid(Medikit).name()) {
            // Delete Medikit Entity
            entityMap[(int)InteractedEntity->mapPos.x][(int)InteractedEntity->mapPos.y] = nullptr;
            map[(int)InteractedEntity->mapPos.y][(int)InteractedEntity->mapPos.x] = '0';
            entities.remove(InteractedEntity);
            delete InteractedEntity; InteractedEntity = nullptr;

            // Increase Player's life
            player.increaseLife();
        }
        else if (typeid(*InteractedEntity).name() == typeid(Ammo).name()) {
            // Delete Ammo Entity
            entityMap[(int)InteractedEntity->mapPos.x][(int)InteractedEntity->mapPos.y] = nullptr;
            map[(int)InteractedEntity->mapPos.y][(int)InteractedEntity->mapPos.x] = '0';
            entities.remove(InteractedEntity);
            delete InteractedEntity; InteractedEntity = nullptr;

            // Increase player's Ammo
            player.increaseAmmo();
        }
        else if (typeid(*InteractedEntity).name() == typeid(Key).name()) {
            // Delete Ammo Entity
            entityMap[(int)InteractedEntity->mapPos.x][(int)InteractedEntity->mapPos.y] = nullptr;
            map[(int)InteractedEntity->mapPos.y][(int)InteractedEntity->mapPos.x] = '0';
            entities.remove(InteractedEntity);

            Key* key = static_cast<Key*>(InteractedEntity);

            // Opened the corresponding door
            for (int x = 0; x < mapSize; x++) {
                for (int y = 0; y < mapSize; y++) {
                    if (map[x][y] == key->getKeyCode()) map[x][y] = '0';
                }
            }

            // Delete the key object
            delete key; key = nullptr;
            InteractedEntity = nullptr;
        }
        else if (typeid(*InteractedEntity).name() == typeid(Portal).name()) {
            // StateMainMenu* stateMainMenu = new StateMainMenu(this->gameManager);
            // this->gameManager->changeState(stateMainMenu);
            // return;
        }
    }
#pragma endregion

#pragma region Rendering Textured Entities (Sprites)
    // Calculate distance for every entities
    for (Entity* entity : entities) {
        if (entity->getToDraw()) entity->calculateDistanceUntilPlayer(player);

        if (typeid(*entity).name() == typeid(Bullet).name()) {
            Bullet* bullet = static_cast<Bullet*>(entity);
            // Check if the bullet hit something
            int nextX = floor((float)bullet->mapPos.x + 0.5 + bullet->getVelocity().x * dt * 10.f);
            int nextY = floor((float)bullet->mapPos.y + 0.5 + bullet->getVelocity().y * dt * 10.f);

            if (nextX < 0 || nextY < 0 || nextX > mapSize - 1 || nextY > mapSize - 1) {
                bullet->isTravelling = false;
                bullet->isExplosing = true;
            }
            else if (map[nextY][nextX] == '1') { // Bullet and Wall collision
                bullet->isTravelling = false;
                bullet->isExplosing = true;
            }
            else if (nextX == floor(player.position.x) && nextY == floor(player.position.y) && !bullet->getIsPlayerBullet()) // Ennemies bullets and Player collision
            {
                if (bullet->isExplosing == false) player.loseLife();

                // bullet->isTravelling = false;
                // bullet->isExplosing = true;
                bullet->setToRemove(true);

                // If player is dead, lauch gameOver menu
            }
            else if (map[nextY][nextX] == 'E' && bullet->getIsPlayerBullet()) { // Player's bullet and Ennemies collision
                if (bullet->isExplosing == false) {
                    Ennemy* ennemy = static_cast<Ennemy*>(entityMap[nextX][nextY]);
                    if (ennemy != nullptr) {
                        ennemy->decreaseHP(bullet->getDamage());
                        // Remove the ennemy if his HP are under 1
                        if (ennemy->getHP() <= 0) {
                            ennemy->setIsDying();
                        }
                    }
                }
                bullet->isTravelling = false;
                bullet->isExplosing = true;
            }
        }
    }

    // Clear dead ennemies and opened chests
    for (int x = 0; x < 32; x++) {
        for (int y = 0; y < 32; y++) {
            Entity* entity = entityMap[x][y];
            if (entity != nullptr) {
                if (typeid(*entity).name() == typeid(Ennemy).name()) {
                    Ennemy* ennemy = static_cast<Ennemy*>(entity);
                    if (ennemy->getToRemove()) {
                        Entity* droppedEntity = ennemy->getDroppedEntity();
                        entityMap[(int)ennemy->mapPos.x][(int)ennemy->mapPos.y] = droppedEntity;
                        entities.push_back(droppedEntity);
                        map[(int)ennemy->mapPos.y][(int)ennemy->mapPos.x] = 'L';
                        entities.remove(ennemy);
                        delete ennemy; ennemy = nullptr;
                    }
                }
                else if (typeid(*entity).name() == typeid(Chest).name()) {
                    // Replace opened chests by their dropped entity
                    Chest* chest = static_cast<Chest*>(entity);
                    if (chest->getToRemove()) {
                        Entity* droppedEntity = chest->getDroppedEntity();
                        entityMap[(int)chest->mapPos.x][(int)chest->mapPos.y] = droppedEntity;
                        entities.push_back(droppedEntity);
                        map[(int)chest->mapPos.y][(int)chest->mapPos.x] = 'L';
                        entities.remove(chest);
                        delete chest; chest = nullptr;
                    }
                }
            }
        }
    }

    entities.remove_if([](Entity* b) {
        if (b->getToRemove()) {
            delete b;
            return true;
        }
        return false;
    });

    // Sort entities by distanceFromPlayer using lambda expression (needed to avoid overlapping sprites)
    entities.sort([](Entity* e1, Entity* e2) { return (abs(e1->getDistance()) > abs(e2->getDistance())); });

    // Draw and update all entities
    for (Entity* entity : entities) {
        if (typeid(*entity).name() == typeid(Ennemy).name()) {
            Ennemy* ennemy = static_cast<Ennemy*>(entity);
            // Calculate the direction of the bullet (aiming the player)
            sf::Vector2f bulletDir = sf::Vector2f(player.position.x - 0.5, player.position.y - 0.5) - ennemy->mapPos;
            // Get the norm of the direction vector
            double norm = sqrt(pow(bulletDir.x, 2) + pow(bulletDir.y, 2));
            // Get the unit vector
            sf::Vector2f bulletDirUnit = sf::Vector2f(bulletDir.x / norm, bulletDir.y / norm);
            Bullet* bullet = ennemy->shoot(bulletDirUnit, this->player.position, this->map);
            if (bullet != nullptr) entities.push_back(bullet);
        }
        entity->draw(*gameManager->getRenderWindow(), player, ZBuffer, gameManager->getWindowWidth(), gameManager->getWindowHeight());
        entity->update(dt); // Update the animation
    }

#pragma endregion

#pragma region Rendering player sprites
    player.draw(*gameManager->getRenderWindow());
    player.update(dt);
    showCursor();
#pragma endregion
}

void StatePlayGame::parseMap2D()
{
    std::string tempText;
    std::ifstream mapFile;
    std::string mapLocation = mapFileFolder + mapFileName;
    mapFile.open(mapLocation);

    srand(time(NULL)); // Randomize seed
    int rnd = 0;

    int indexX = 0, indexY = 0;
    while (std::getline(mapFile, tempText))
    {
        for (auto it = tempText.cbegin(); it != tempText.cend(); ++it)
        {
            map[indexX][indexY] = *it;
            if (map[indexX][indexY] == 'T') // Player spawn position
            {
                player.position = sf::Vector2f(indexY + 0.5, indexX + 0.5);
            }
            else if (map[indexX][indexY] == 'E') { // Ennemy
                rnd = (rand() % 2); // Between 0 and 1
                Ennemy* ennemy = new Ennemy(1, sf::Vector2f((float)indexY, (float)indexX), rnd);
                entities.push_back(ennemy);
                entityMap[indexY][indexX] = ennemy;
            }
            else if (map[indexX][indexY] == 'C') { // Chest
                rnd = (rand() % 2); // Between 0 and 1
                Chest* chest = new Chest(1, sf::Vector2f((float)indexY, (float)indexX), rnd);
                entities.push_back(chest);
                entityMap[indexY][indexX] = chest;
            }
            else if (map[indexX][indexY] == '1' || map[indexX][indexY] == '0') {
                entityMap[indexY][indexX] = nullptr;
            }
            else if (map[indexX][indexY] == 'd') {
                Key* key = new Key(1, sf::Vector2f((float)indexY, (float)indexX), AnimatedVertexArray("../PoutineStyle/pics/key.png", 64, 64, 0, 1), 'D');
                entityMap[indexY][indexX] = key;
                entities.push_back(key);
            }
            else if (map[indexX][indexY] == 'v') {
                Key* key = new Key(1, sf::Vector2f((float)indexY, (float)indexX), AnimatedVertexArray("../PoutineStyle/pics/key.png", 64, 64, 1, 1), 'V');
                entityMap[indexY][indexX] = key;
                entities.push_back(key);
            }
            else if (map[indexX][indexY] == 'w'){
                Key* key = new Key(1, sf::Vector2f((float)indexY, (float)indexX), AnimatedVertexArray("../PoutineStyle/pics/key.png", 64, 64, 2, 1), 'W');
                entityMap[indexY][indexX] = key;
                entities.push_back(key);
            }
            else if (map[indexX][indexY] == 'x') {
                Key* key = new Key(1, sf::Vector2f((float)indexY, (float)indexX), AnimatedVertexArray("../PoutineStyle/pics/key.png", 64, 64, 3, 1), 'X');
                entityMap[indexY][indexX] = key;
                entities.push_back(key);
            }
            else if (map[indexX][indexY] == 'y') {
                Key* key = new Key(1, sf::Vector2f((float)indexY, (float)indexX), AnimatedVertexArray("../PoutineStyle/pics/key.png", 64, 64, 4, 1), 'Y');
                entityMap[indexY][indexX] = key;
                entities.push_back(key);
            }
            else if (map[indexX][indexY] == 'z'){
                Key* key = new Key(1, sf::Vector2f((float)indexY, (float)indexX), AnimatedVertexArray("../PoutineStyle/pics/key.png", 64, 64, 5, 1), 'Z');
                entityMap[indexY][indexX] = key;
                entities.push_back(key);
            }
            else if (map[indexX][indexY] == 'S') {
                Portal* portal = new Portal(1, sf::Vector2f((float)indexY, (float)indexX));
                entityMap[indexY][indexX] = portal;
                entities.push_back(portal);
            }
            indexY++;
        }
        indexX++;
        indexY = 0;
    }

    mapFile.close();
}

void StatePlayGame::hud()
{
    sf::RectangleShape hudUp, hudDownL, hudDownML, hudDownM, hudDownMR, hudDownR;
    float widthPos = gameManager->getWindowWidth() / gameManager->getWindowWidth();
    float hudDownWidth = widthPos * (gameManager->getWindowWidth() / 5)-3;
    float heightPos = gameManager->getWindowHeight() / gameManager->getWindowHeight();
    sf::Color lineCol = sf::Color::Red;
    sf::Color hudBack = sf::Color::White;

    hudUp.setSize(sf::Vector2f(gameManager->getWindowWidth(), gameManager->getWindowHeight() / 25));
    hudDownL.setSize(sf::Vector2f(hudDownWidth, gameManager->getWindowHeight() / 10));
    hudDownML.setSize(sf::Vector2f(hudDownWidth, gameManager->getWindowHeight() / 10));
    hudDownM.setSize(sf::Vector2f(hudDownWidth, gameManager->getWindowHeight() / 10));
    hudDownMR.setSize(sf::Vector2f(hudDownWidth, gameManager->getWindowHeight() / 10));
    hudDownR.setSize(sf::Vector2f(hudDownWidth, gameManager->getWindowHeight() / 10));

    hudUp.setFillColor(hudBack);
    hudUp.setOutlineColor(lineCol);
    hudUp.setOutlineThickness(3);
    hudUp.setPosition(0, 0);

    hudDownL.setFillColor(hudBack);
    hudDownL.setOutlineColor(lineCol);
    hudDownL.setOutlineThickness(3);
    hudDownL.setPosition(3, gameManager->getWindowHeight() - gameManager->getWindowHeight() / 10-3);

    hudDownML.setFillColor(hudBack);
    hudDownML.setOutlineColor(lineCol);
    hudDownML.setOutlineThickness(3);
    hudDownML.setPosition(hudDownWidth+3, gameManager->getWindowHeight() - gameManager->getWindowHeight() / 10-3);

    hudDownM.setFillColor(hudBack);
    hudDownM.setOutlineColor(lineCol);
    hudDownM.setOutlineThickness(3);
    hudDownM.setPosition(hudDownWidth * 2+6, gameManager->getWindowHeight() - gameManager->getWindowHeight() / 10-3);

    hudDownMR.setFillColor(hudBack);
    hudDownMR.setOutlineColor(lineCol);
    hudDownMR.setOutlineThickness(3);
    hudDownMR.setPosition(hudDownWidth * 3+9, gameManager->getWindowHeight() - gameManager->getWindowHeight() / 10-3);

    hudDownR.setFillColor(hudBack);
    hudDownR.setOutlineColor(lineCol);
    hudDownR.setOutlineThickness(3);
    hudDownR.setPosition(hudDownWidth * 4+12, gameManager->getWindowHeight() - gameManager->getWindowHeight() / 10-3);

    gameManager->getRenderWindow()->draw(hudUp);
    gameManager->getRenderWindow()->draw(hudDownL);
    gameManager->getRenderWindow()->draw(hudDownML);
    gameManager->getRenderWindow()->draw(hudDownM);
    gameManager->getRenderWindow()->draw(hudDownMR);
    gameManager->getRenderWindow()->draw(hudDownR);


    sf::Font font = sf::Font();
    sf::Color fontCol = sf::Color::Red;
    font.loadFromFile("CollegiateBlackFLF.ttf");

    sf::Text liveText("Live : ", font, 15);
    sf::Text live("", font, 15);
    live.setString(std::to_string(player.getLive()));
    sf::Text health("Health :", font, 15);
    sf::RectangleShape visualHealth;
    sf::Text arme("weapon", font, 15);
    sf::Text ammunition("Ammo :", font, 15);
    sf::Text currentAmmunition("", font, 15);
    currentAmmunition.setString(std::to_string(player.getCurrentAmmunition()) +" / " + std::to_string(player.getAmmunition()));
    sf::Text score("Score :", font, 15);
    sf::Text currentScore("", font, 15);
    currentScore.setString(std::to_string(player.getScore()));

    liveText.setFillColor(fontCol);
    liveText.setPosition(sf::Vector2f(5, gameManager->getWindowHeight() - heightPos * 50));

    live.setFillColor(fontCol);
    live.setPosition(sf::Vector2f(5, gameManager->getWindowHeight() - heightPos * 25));

    health.setFillColor(fontCol);
    health.setPosition(sf::Vector2f(hudDownWidth+6, gameManager->getWindowHeight() - heightPos * 50));

    if (player.getHealth() <= 0)
    {
        visualHealth.setSize(sf::Vector2f(1, 25));
    }
    else
    {
        visualHealth.setSize(sf::Vector2f((hudDownWidth / 100) * player.getHealth(), 25));
    }
    visualHealth.setFillColor(sf::Color::Green);
    visualHealth.setPosition(sf::Vector2f(hudDownWidth+ 3, gameManager->getWindowHeight() - heightPos * 28));

    arme.setFillColor(fontCol);
    arme.setPosition(sf::Vector2f(hudDownWidth * 2 + 9, gameManager->getWindowHeight() - heightPos * 50));

    ammunition.setFillColor(fontCol);
    ammunition.setPosition(sf::Vector2f(hudDownWidth * 3 + 12, gameManager->getWindowHeight() - heightPos * 50));

    currentAmmunition.setFillColor(fontCol);
    currentAmmunition.setPosition(sf::Vector2f(hudDownWidth * 3 + 12, gameManager->getWindowHeight() - heightPos * 25));

    score.setFillColor(fontCol);
    score.setPosition(sf::Vector2f(hudDownWidth * 4 + 15, gameManager->getWindowHeight() - heightPos * 50));

    currentScore.setFillColor(fontCol);
    currentScore.setPosition(sf::Vector2f(hudDownWidth * 4 + 15 , gameManager->getWindowHeight() - heightPos * 25));

    gameManager->getRenderWindow()->draw(liveText);
    gameManager->getRenderWindow()->draw(live);
    gameManager->getRenderWindow()->draw(health);
    gameManager->getRenderWindow()->draw(visualHealth);
    gameManager->getRenderWindow()->draw(arme);//TODO remplacere le text par une image de l'arme utilisé
    gameManager->getRenderWindow()->draw(ammunition);
    gameManager->getRenderWindow()->draw(currentAmmunition);
    gameManager->getRenderWindow()->draw(score);
    gameManager->getRenderWindow()->draw(currentScore);

    if (player.dead())
    {
        StateGameOverMenu* gameOverMenu = new StateGameOverMenu(this->gameManager, false);
        this->gameManager->getRenderWindow()->setMouseCursorVisible(true);
        this->gameManager->changeState(gameOverMenu);
        return;
    }

}

void StatePlayGame::showCursor()
{
    yOffset = 60;
    sf::Sprite aimCursor;
    aimCursor.setTexture(imgAimCursor);
    aimCursor.setScale(0.5, 0.5);

    sf::Vector2u cursorSize = imgAimCursor.getSize();
    int cursorWidth = cursorSize.x, cursorHeigth = cursorSize.y;

    sf::Vector2f centerWindowPos = sf::Vector2f(this->gameManager->getWindowWidth() / 2, this->gameManager->getWindowHeight() / 2);

    aimCursor.setPosition(centerWindowPos.x - (cursorWidth / 4.5), centerWindowPos.y - (cursorHeigth / 4));

    this->gameManager->getRenderWindow()->draw(aimCursor);
}

/// <summary>
/// Get the entity facing the player (1 block away max), otherwise nullptr
/// </summary>
/// <returns>Return * Entity or nullptr</returns>
Entity* StatePlayGame::getInteractedEntity() {
    int playerDirectionPosX = floor(player.position.x + 1.0 * player.direction.x);
    int playerDirectionPosY = floor(player.position.y + 1.0 * player.direction.y);
    if (playerDirectionPosX > 0 && playerDirectionPosX < mapSize && playerDirectionPosY > 0 && playerDirectionPosY < mapSize) {
        if (this->entityMap[playerDirectionPosX][playerDirectionPosY] != nullptr) return entityMap[playerDirectionPosX][playerDirectionPosY];
    }
    /*for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            int entityPosX = playerDirectionPosX + x;
            int entityPosY = playerDirectionPosY + y;
            if (entityPosX > 0 && entityPosX < mapSize && entityPosY > 0 && entityPosY < mapSize) {
                if (this->entityMap[entityPosX][entityPosY] != nullptr) return entityMap[entityPosX][entityPosY];
            }
        }
    }*/
    return nullptr;
}