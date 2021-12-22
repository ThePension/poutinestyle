#include "StatePlayGame.h"

StatePlayGame::StatePlayGame(GameManager* game, Settings settings, std::string mapFilePath, int mapSize)
{
    // Settings
    this->settings = settings;

    this->speedFactor = this->settings.getSensibility();

    /************************************************************ to something with those settings
    this->settings.getDifficulty();
    this->settings.getShowMetaData();
    */
    // this->settings.getVolume(); // pas encore utile

    switch (this->settings.getLevel())
    {
    case 0:
        mapFilePath = "Map_Example3.txt";
        mapSize = 32;
        // this->levels.insert(std::pair<std::string, int>("Map_Example3.txt", 32));
        this->levels.insert(std::pair<std::string, int>("Lvl2.txt", 16));
        this->levels.insert(std::pair<std::string, int>("Lvl3.txt", 32));
        this->levels.insert(std::pair<std::string, int>("Lvl4.txt", 32));
        this->levels.insert(std::pair<std::string, int>("Lvl5.txt", 64));
        break;
    case 1:
        mapFilePath = "Lvl1.txt";
        mapSize = 16;
        break;
    case 2:
        mapFilePath = "Lvl2.txt";
        mapSize = 16;
        break;
    case 3:
        mapFilePath = "Lvl3.txt";
        mapSize = 32;
        break;
    case 4:
        mapFilePath = "Lvl4.txt";
        mapSize = 32;
        break;
    case 5:
        mapFilePath = "Lvl5.txt";
        mapSize = 64;
        break;
    }

    player = new Player();

    this->gameManager = game;
    this->mapFilePath = "Map/" + mapFilePath;
    this->mapSize = mapSize;

    this->actualLevel = this->levels.begin();
    
    gameManager->getRenderWindow()->setMouseCursorVisible(false);
    gameManager->getRenderWindow()->setMouseCursorGrabbed(true); // The mouse can't leave the window

    oldMouseX = sf::Mouse::getPosition().x;
    sf::Mouse::setPosition(sf::Vector2i(gameManager->getWindowWidth() / 2, gameManager->getWindowHeight() / 2));

    linesFloor = new sf::VertexArray(sf::Lines, 2);
    lines = new sf::VertexArray(sf::Lines, 2 * gameManager->getWindowWidth()); // Must be bigger if we want to draw floors and ceilings
    linesOverride = new sf::VertexArray(sf::Lines, 2);

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
    wallTextures.loadFromFile("../PoutineStyle/pics/wallTextures3.png");

    // Load cursor texture
    imgAimCursor.loadFromFile("Cursor/cursorAim3.png");
    setHud();
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
    cleanAllEntitys();
    delete hudUp; delete hudDownL; delete hudDownML; delete hudDownM; delete hudDownMR; delete hudDownR;
    delete player; player = nullptr;
    delete[] *(this->map);
    delete[] this->map;
    delete linesFloor; linesFloor = nullptr;
    delete lines; lines = nullptr;
    delete linesOverride; linesOverride = nullptr;
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
                player->direction = rotateVectorMatrix(player->direction, -speedFactor * deltatime); // Rotate the player direction
                player->planeVec = rotateVectorMatrix(player->planeVec, -speedFactor * deltatime); // Rotate plane direction
            }
            else if (oldMouseX < mouseX)  // go to right | 0 --- oldMouseX -- < -- mouseX --- maxWidth
            {
                player->direction = rotateVectorMatrix(player->direction, speedFactor * deltatime); // Rotate the player direction
                player->planeVec = rotateVectorMatrix(player->planeVec, speedFactor * deltatime); // Rotate plane direction
            }
            
            oldMouseX = mouseX;
        }

        if (event.type == sf::Event::KeyPressed)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) isMapDisplayed = !isMapDisplayed; // Toggle map display
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) player->reload();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) wPressed = true;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) aPressed = true;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) sPressed = true;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) dPressed = true;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) movingSpeed = 5;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) InteractedEntity = getInteractedEntity();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) pause();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) player->switchWeapon();
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
            if (typeid(*player->getCurrentWeapon()).name() == typeid(Knife).name()) {
                if (player->getCurrentWeapon()->getShootAnimation().isAnimationOver) {
                    player->shoot(player->direction);
                    Entity* entity = getInteractedEntity();
                    if (entity != nullptr) {
                        if (typeid(*entity).name() == typeid(Guard).name() || typeid(*entity).name() == typeid(General).name()) {
                            Ennemy* ennemy = static_cast<Ennemy*>(entity);
                            if (!ennemy->getIsDying()) {
                                ennemy->decreaseHP(player->getCurrentWeapon()->getDamage());
                                // Remove the ennemy if his HP are under 1
                                if (ennemy->getHP() <= 0) {
                                    ennemy->setIsDying();
                                }
                            }
                        }
                    }
                }
            }
            else{
                std::stack<Bullet*> bullets = player->shoot(player->direction);
                while(!bullets.empty()) {
                    Bullet* bullet = bullets.top();
                    if (bullet != nullptr) {
                        entities.push_back(bullet);
                    }
                    bullets.pop();
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
        newPlayerPos = sf::Vector2f(player->position.x - player->planeVec.x * movingSpeed * deltaTime, player->position.y - player->planeVec.y * movingSpeed * deltaTime);
        updatePlayerPosition(newPlayerPos);
    }

    if (dPressed)
    {
        newPlayerPos = sf::Vector2f(player->position.x + player->planeVec.x * movingSpeed * deltaTime, player->position.y + player->planeVec.y * movingSpeed * deltaTime);
        updatePlayerPosition(newPlayerPos);
    }

    if (wPressed)
    {
        newPlayerPos = sf::Vector2f(player->position.x + player->direction.x * movingSpeed * deltaTime, player->position.y + player->direction.y * movingSpeed * deltaTime);
        updatePlayerPosition(newPlayerPos);
    }

    if (sPressed)
    {
        newPlayerPos = sf::Vector2f(player->position.x - player->direction.x * movingSpeed * deltaTime, player->position.y - player->direction.y * movingSpeed * deltaTime);
        updatePlayerPosition(newPlayerPos);
    }

    draw(deltaTime);
}

void StatePlayGame::updatePlayerPosition(sf::Vector2f newPos)
{
    int newPosMapY, newPosMapX, oldPosMapX, oldPosMapY;

    oldPosMapY = floor(player->position.x);
    newPosMapY = newPos.x;
    oldPosMapX = floor(player->position.y);
    newPosMapX = newPos.y;

    // Check X axis
    if (!Entity::isWall(map[newPosMapX][oldPosMapY]))
    {
        // Update player position on the Y axis
        player->position.y = newPos.y;
    }
    // Check Y axis
    if (!Entity::isWall(map[oldPosMapX][newPosMapY]))
    {
        // Update the player position on the X axis
        player->position.x = newPos.x;
    }
}

void StatePlayGame::draw(double dt)
{
    if(isMapDisplayed) drawMap2D();
    else
    {
        renderingWalls(dt);
        renderingEntities(dt);
        displayHud();
        drawMiniMap();
        endGameManagment(); // IMPORTANT ! need to be the last function called here
    }
}

void StatePlayGame::endGameManagment()
{
    if (player->getIsDead())
    {
        StateGameOverMenu* gameOverMenu = new StateGameOverMenu(this->gameManager, false);
        this->gameManager->getRenderWindow()->setMouseCursorVisible(true);
        this->gameManager->changeState(gameOverMenu);
        return;
    }

    if (this->isFinished)
    {
        StateGameOverMenu* gameOverMenu = new StateGameOverMenu(this->gameManager, true);
        this->gameManager->getRenderWindow()->setMouseCursorVisible(true);
        this->gameManager->changeState(gameOverMenu);
        return;
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
    player_circle.setPosition(sf::Vector2f(player->position.x * (blockWidth) - player_circle.getRadius(), player->position.y * (blockHeight - 1) - player_circle.getRadius() / 2.0));
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
        sf::Vertex(sf::Vector2f(player_circle.getPosition().x + player_circle.getRadius() + 16 * player->direction.x, player_circle.getPosition().y + player_circle.getRadius() + 16 * player->direction.y))
    };

    gameManager->getRenderWindow()->draw(playerDirLine, 2, sf::Lines);
}

void StatePlayGame::drawMiniMap() 
{
    // Draw background rectangle
    int w = this->gameManager->getWindowWidth();
    int h = this->gameManager->getWindowHeight();

    int blockWUnit = w / 32;
    int blockHUnit = h / 32;

    sf::RectangleShape rectBackground = sf::RectangleShape();
    rectBackground.setFillColor(sf::Color::White);
    rectBackground.setPosition(blockWUnit - 2, 2 * blockHUnit - 2); // problème ici
    rectBackground.setSize(sf::Vector2f(7* blockWUnit + 4, 7* blockHUnit + 4));
    gameManager->getRenderWindow()->draw(rectBackground);

    for (int x = -3; x <= 3; x++) {
        for (int y = -3; y <= 3; y++) {
            int positionX = floor(player->position.x) + x;
            int positionY = floor(player->position.y) + y;
            
            sf::RectangleShape cell = sf::RectangleShape();
            cell.setPosition(sf::Vector2f((3 - x) * blockWUnit + blockWUnit, (4 - y) * blockHUnit + blockHUnit));
            cell.setSize(sf::Vector2f(blockWUnit, blockHUnit));
            
            if (positionX >= 0 && positionX < mapSize && positionY >= 0 && positionY < mapSize) {
                char charCell = map[positionY][positionX];
                if (Entity::isWall(charCell)) {
                    cell.setFillColor(sf::Color::Red);
                }
                else {
                    cell.setFillColor(sf::Color::White);
                }
                if (charCell == 'D' ||
                    charCell == 'V' ||
                    charCell == 'W' ||
                    charCell == 'X' ||
                    charCell == 'Y' ||
                    charCell == 'Z') 
                {
                    cell.setFillColor(sf::Color(125, 125, 125, 255));
                }
            }else{
                cell.setFillColor(sf::Color::Black);
            }
            gameManager->getRenderWindow()->draw(cell);   
        }
    }

    // Draw player
    sf::CircleShape circle = sf::CircleShape();
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(3 * blockWUnit + blockWUnit, 4 * blockHUnit + blockHUnit);
    circle.setRadius(blockWUnit / 2);
    gameManager->getRenderWindow()->draw(circle);

    // Draw player direction vector
    sf::RectangleShape rect = sf::RectangleShape();
    rect.setPosition(sf::Vector2f(circle.getPosition().x + circle.getRadius(), circle.getPosition().y + circle.getRadius()));
    rect.setSize(sf::Vector2f(2.5, 15));
    rect.setFillColor(sf::Color::Green);

    // Update rotation
    double delta = player->direction.x / player->direction.y;
    double angleInRad = atan(delta);
    double angleInDegrees = angleInRad * 180.0 / 3.1415 + 180.0; // Use a constant
    if (player->direction.y < 0) angleInDegrees += 180.0;
    rect.rotate(-angleInDegrees);
    gameManager->getRenderWindow()->draw(rect);
}

void StatePlayGame::renderingWalls(double dt)
{
#pragma region Rendering Walls
    yOffset = 0; // Used to create the illusion of a taller player
    int w = gameManager->getWindowWidth();
    
    for (int x = 0; x < w; x++) {
        castRay(x, w, 0);
    }

    // Draw walls with textures
    gameManager->getRenderWindow()->draw(*lines, &wallTextures);
    lines->clear();
    lines->resize(2 * w);
#pragma endregion
}

void StatePlayGame::castRay(int x, int w, int depth)
{
    int countTransparentWalls = 0;
    
    // Cell where the player is standing
    sf::Vector2i playerMapPos = sf::Vector2i(int(player->position.x), int(player->position.y));

    // Vector representing the direction of the actual ray
    double cameraX = double(2.f * double(x)) / double(w) - 1.0;

    sf::Vector2f rayDir = player->direction + sf::Vector2f(player->planeVec.x * cameraX, player->planeVec.y * cameraX);
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
        sideDistX = ((player->position.x) - double(playerMapPos.x)) * deltaDistX;
    }
    else {
        stepX = 1;
        sideDistX = (double(playerMapPos.x) + 1.f - (player->position.x)) * deltaDistX;
    }
    if (rayDir.y < 0) {
        stepY = -1;
        sideDistY = ((player->position.y) - double(playerMapPos.y)) * deltaDistY;
    }
    else {
        stepY = 1;
        sideDistY = (double(playerMapPos.y) + 1.f - (player->position.y)) * deltaDistY;
    }
    int ceilingPixel = 0; // position of ceiling pixel on the screen
    int groundPixel = gameManager->getWindowHeight(); // position of ground pixel on the screen
    sf::Color color1 = sf::Color(100, 100, 100), color2 = sf::Color(150, 150, 150);
    sf::Color floorColor = ((playerMapPos.x % 2 == 0 && playerMapPos.y % 2 == 0) || (playerMapPos.x % 2 == 1 && playerMapPos.y % 2 == 1)) ? color1 : color2;
    double perpWallDist = 1.0;
    Wall* currentWall = nullptr;
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
        if (playerMapPos.y >= 0 && playerMapPos.y < mapSize && playerMapPos.x >= 0 && playerMapPos.x < mapSize) {
            if (Entity::isWall(map[playerMapPos.y][playerMapPos.x]) || map[playerMapPos.y][playerMapPos.x] == 'B')
            {
                Wall* wall = static_cast<Wall*>(entityMap[playerMapPos.x][playerMapPos.y]);
                if (wall->getIsTransparent()) {
                    if (countTransparentWalls == depth && depth < 3) {
                        castRay(x, w, depth+1);
                        wallHit = true;
                        currentWall = wall;
                    }
                    
                    countTransparentWalls++;
                }
                else {
                    wallHit = true;
                    currentWall = wall;
                }
            }
            else 
            { 
                if (entityMap[playerMapPos.x][playerMapPos.y] != nullptr) {
                    entityMap[playerMapPos.x][playerMapPos.y]->setToDraw(true);
                }
            }
            if (isWallHitHorizontal) perpWallDist = sideDistX - deltaDistX;
            else perpWallDist = sideDistY - deltaDistY;

            // Set the floor
            double wallHeight = int(gameManager->getWindowHeight() / perpWallDist);
            
            (*linesFloor)[0] = sf::Vertex(sf::Vector2f((float)x, (float)groundPixel + yOffset), floorColor);
            groundPixel = int(wallHeight * 0.495 + double(gameManager->getWindowHeight()) * 0.5f);
            (*linesFloor)[1] = sf::Vertex(sf::Vector2f((float)x, (float)groundPixel + yOffset), floorColor);
            
            // Draw floor
            if(floorColor == color1) gameManager->getRenderWindow()->draw(*linesFloor);

            if (floorColor == color1) floorColor = color2;
            else floorColor = color1;
        }
        else {
            wallHit = true;
        }
    }
 
    if (playerMapPos.y >= 0 && playerMapPos.y < mapSize && playerMapPos.x >= 0 && playerMapPos.x < mapSize) {
        sf::Color wallColor;

        if (isWallHitHorizontal) wallColor = sf::Color::White;
        else wallColor = sf::Color(126, 126, 126);

        int lineHeight = int(gameManager->getWindowHeight() / perpWallDist);

        int drawStart = -lineHeight / 2 + gameManager->getWindowHeight() / 2;
        int drawEnd = lineHeight / 2 + gameManager->getWindowHeight() / 2;

        // Texture stuff
        sf::Vector2i texture_coords = currentWall->getCurrentTextureCoordinates() * textureSize;

        // Calculate where the wall was hit
        float wallX;
        if (isWallHitHorizontal) wallX = (player->position.y) + perpWallDist * rayDir.y;
        else wallX = (player->position.x) + perpWallDist * rayDir.x;
        wallX -= floor(wallX);

        // Get x coordinate on the wall texture
        int texX = int(wallX * float(textureSize));
        if ((isWallHitHorizontal && rayDir.x > 0) || (!isWallHitHorizontal && rayDir.y < 0))
            texX = textureSize - texX - 1;

        texture_coords.x += texX;

        if (depth > 0) { // If the ray went through a transparent wall
            // Create a line that will be displayed behind the transparent wall
            
            sf::Vertex lineUp, lineBottom;
            
            lineUp.position = sf::Vector2f((float)x, (float)drawStart + yOffset);
            lineUp.color = wallColor;
            lineUp.texCoords = sf::Vector2f((float)texture_coords.x, (float)texture_coords.y + 1);

            lineBottom.position = sf::Vector2f((float)x, (float)drawEnd + yOffset);
            lineBottom.color = wallColor;
            lineBottom.texCoords = sf::Vector2f((float)texture_coords.x, (float)(texture_coords.y + textureSize - 1));

            (*linesOverride)[0] = lineUp;
            (*linesOverride)[1] = lineBottom;

            gameManager->getRenderWindow()->draw(*linesOverride, &wallTextures);
        }
        else 
        {
            // Adding vertical lines in ArrayVertex, and set the coordinates of the texture to use
            // x * 2 are all the first points of the lines (top ones) (more info there : https://www.sfml-dev.org/tutorials/2.5/graphics-vertex-array.php)
            (*lines)[x * 2].position = sf::Vector2f((float)x, (float)drawStart + yOffset);
            (*lines)[x * 2].color = wallColor;
            (*lines)[x * 2].texCoords = sf::Vector2f((float)texture_coords.x, (float)texture_coords.y + 1);
            // x * 2 + 1 are all the seconds points of the lines (bottom ones)
            (*lines)[x * 2 + 1].position = sf::Vector2f((float)x, (float)drawEnd + yOffset);
            (*lines)[x * 2 + 1].color = wallColor;
            (*lines)[x * 2 + 1].texCoords = sf::Vector2f((float)texture_coords.x, (float)(texture_coords.y + textureSize - 1));
            //if(!currentWall->getIsTransparent()) ZBuffer[x] = perpWallDist; // Needed for entities rendering
            ZBuffer[x] = perpWallDist; // Needed for entities rendering
        }
    }
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
            player->increaseLife();
        }
        else if (typeid(*InteractedEntity).name() == typeid(Ammo).name()) {
            // Delete Ammo Entity
            entityMap[(int)InteractedEntity->mapPos.x][(int)InteractedEntity->mapPos.y] = nullptr;
            map[(int)InteractedEntity->mapPos.y][(int)InteractedEntity->mapPos.x] = '0';
            entities.remove(InteractedEntity);
            delete InteractedEntity; InteractedEntity = nullptr;

            // Increase player's Ammo
            player->increaseAmmo();
        }
        else if (typeid(*InteractedEntity).name() == typeid(Key).name()) {
            // Delete Key Entity
            entityMap[(int)InteractedEntity->mapPos.x][(int)InteractedEntity->mapPos.y] = nullptr;
            map[(int)InteractedEntity->mapPos.y][(int)InteractedEntity->mapPos.x] = '0';
            entities.remove(InteractedEntity);

            Key* key = static_cast<Key*>(InteractedEntity);
            player->addKey(key);

            InteractedEntity = nullptr;
        }
        else if (typeid(*InteractedEntity).name() == typeid(Door).name()) {
            Door* door = static_cast<Door*>(InteractedEntity);
            if (door->getIsSecretPassage()) {
                door->setOpening();
            }
            else {
                for (Key* key : player->getPlayerKeys()) {
                    if (map[(int)InteractedEntity->mapPos.y][(int)InteractedEntity->mapPos.x] == key->getKeyCode()) door->setOpening();
                }
            }
            InteractedEntity = nullptr;
        }
        else if (typeid(*InteractedEntity).name() == typeid(Portal).name())
        {
            // from a level to another 
            if (this->actualLevel != this->levels.end())
            {
                delete[] *(this->map);
                delete[] this->map;
                map = nullptr;

                player->clearKeys();

                cleanAllEntitys();

                this->mapFilePath = "Map/" + this->actualLevel->first;
                this->mapSize = this->actualLevel->second;

                this->actualLevel++;

                this->blockWidth = gameManager->getWindowWidth() / mapSize;
                this->blockHeight = gameManager->getWindowHeight() / mapSize;

                map = new char* [mapSize];
                for (int i = 0; i < mapSize; i++)
                {
                    map[i] = new char[mapSize];
                    for (int j = 0; j < mapSize; j++)
                    {
                        map[i][j] = '0';
                    }
                }
                parseMap2D();

                InteractedEntity = nullptr;
                return;
            }
            else
            {
                this->isFinished = true;
            }
        }
        else if (typeid(*InteractedEntity).name() == typeid(Pistol).name() || typeid(*InteractedEntity).name() == typeid(Shotgun).name() || typeid(*InteractedEntity).name() == typeid(GrenadeLauncher).name()) {
            Weapon* weapon = static_cast<Weapon*>(InteractedEntity);
            Weapon* oldWeapon = player->setWeapon(weapon);
        
            entities.remove(weapon);
            if (oldWeapon != nullptr) {
                entities.push_back(oldWeapon);
                oldWeapon->mapPos = weapon->mapPos;
                map[(int)InteractedEntity->mapPos.y][(int)InteractedEntity->mapPos.x] = '0';
            }
            entityMap[(int)InteractedEntity->mapPos.x][(int)InteractedEntity->mapPos.y] = oldWeapon;
            InteractedEntity = nullptr;
        }
    }
    InteractedEntity = nullptr;
#pragma endregion

#pragma region Rendering Textured Entities (Sprites)
    // Calculate distance for every entities
    for (Entity* entity : entities) {
        if (entity->getToDraw()) entity->calculateDistanceUntilPlayer(player->position);

        if (typeid(*entity).name() == typeid(Bullet).name()) {
            Bullet* bullet = static_cast<Bullet*>(entity);
            // Check if the bullet hit something
            int nextX = floor((float)bullet->mapPos.x + 0.5 + bullet->getVelocity().x * dt * 10.f);
            int nextY = floor((float)bullet->mapPos.y + 0.5 + bullet->getVelocity().y * dt * 10.f);

            if (nextX < 0 || nextY < 0 || nextX > mapSize - 1 || nextY > mapSize - 1) {
                bullet->isTravelling = false;
                bullet->isExplosing = true;
            }
            else if(Entity::isWall(map[nextY][nextX])) // Bullet and Wall collision
            {
                if (bullet->getIsGrenade() && !bullet->isExplosing) // Zone explosion
                {
                    this->bulletExplosion(nextX, nextY, bullet->getDamage());
                }
                bullet->isTravelling = false;
                bullet->isExplosing = true;
            }
            else if (nextX == floor(player->position.x) && nextY == floor(player->position.y) && !bullet->getIsPlayerBullet()) // Ennemies bullets and Player collision
            {
                if (bullet->isExplosing == false) player->loseLife();

                bullet->setToRemove(true);
            }
            else if ((map[nextY][nextX] == 'E' || map[nextY][nextX] == 'G') && bullet->getIsPlayerBullet()) { // Player's bullet and Ennemies collision
                if (bullet->getIsGrenade() && !bullet->isExplosing) // Zone explosion
                {
                    this->bulletExplosion(nextX, nextY, bullet->getDamage());
                }
                else if (!bullet->isExplosing) {
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

    // Clear dead ennemies and opened chests and doors
    for (int x = 0; x < 32; x++) {
        for (int y = 0; y < 32; y++) {
            Entity* entity = entityMap[x][y];
            if (entity != nullptr) {
                if (typeid(*entity).name() == typeid(Guard).name() || typeid(*entity).name() == typeid(General).name()) {
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
                else if (typeid(*entity).name() == typeid(Door).name()) {
                    // Remove open door
                    if (entity->getToRemove()) {
                        entityMap[(int)entity->mapPos.x][(int)entity->mapPos.y] = nullptr;
                        map[(int)entity->mapPos.y][(int)entity->mapPos.x] = '0';
                        entities.remove(entity);
                        delete entity; entity = nullptr;
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
        if (typeid(*entity).name() == typeid(Guard).name() || typeid(*entity).name() == typeid(General).name()) {
            Ennemy* ennemy = static_cast<Ennemy*>(entity);
            // Calculate the direction of the bullet (aiming the player)
            sf::Vector2f bulletDir = sf::Vector2f(player->position.x - 0.5, player->position.y - 0.5) - ennemy->mapPos;
            // Get the norm of the direction vector
            double norm = sqrt(pow(bulletDir.x, 2) + pow(bulletDir.y, 2));
            // Get the unit vector
            sf::Vector2f bulletDirUnit = sf::Vector2f(bulletDir.x / norm, bulletDir.y / norm);
            std::stack<Bullet*> bullets = ennemy->shoot(bulletDirUnit, this->player->position, this->map);
            while (!bullets.empty()) {
                Bullet* bullet = bullets.top();
                if (bullet != nullptr) entities.push_back(bullet);
                bullets.pop();
            }
        }
        entity->draw(*gameManager->getRenderWindow(), player->position, player->direction, player->planeVec, ZBuffer, gameManager->getWindowWidth(), gameManager->getWindowHeight());
        entity->update(dt); // Update the animation
    }

#pragma endregion

#pragma region Rendering player sprites
    player->draw(*gameManager->getRenderWindow());
    player->update(dt);
    showCursor();
#pragma endregion
}

void StatePlayGame::parseMap2D()
{
    entities.clear();

    std::string tempText;
    std::ifstream mapFile;

    mapFile.open(this->mapFilePath);

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
                player->position = sf::Vector2f(indexY + 0.5, indexX + 0.5);
            }
            else if (map[indexX][indexY] == 'E') { // Ennemy
                rnd = (rand() % 4); // Between 0 and 3
                Ennemy* guard = new Guard(sf::Vector2f((float)indexY, (float)indexX), rnd);
                entities.push_back(guard);
                entityMap[indexY][indexX] = guard;
            }
            else if (map[indexX][indexY] == 'G') {
                rnd = (rand() % 4); // Between 0 and 3
                Ennemy* general = new General(sf::Vector2f((float)indexY, (float)indexX), rnd);
                entities.push_back(general);
                entityMap[indexY][indexX] = general;
            }
            else if (map[indexX][indexY] == 'C') { // Chest
                rnd = (rand() % 2); // Between 0 and 1
                Chest* chest = new Chest(sf::Vector2f((float)indexY, (float)indexX), rnd);
                entities.push_back(chest);
                entityMap[indexY][indexX] = chest;
            }
            else if(Entity::isWall(map[indexX][indexY]) || map[indexX][indexY] == 'B')
            {
                int y = 0;
                int nbFrames = 1;
                bool isDoor = false;
                bool isSecretPassage = false;
                switch (map[indexX][indexY])
                {
                case '1':
                    y = 0;
                    break;
                case '2':
                    y = 1;
                    break;
                case '3':
                    y = 2;
                    break;
                case '4':
                    y = 3;
                    break;
                case '5':
                    y = 4;
                    break;
                case '6':
                    y = 5;
                    break;
                case 'B':
                case '7':
                    nbFrames = 4;
                    isSecretPassage = true;
                    isDoor = true;
                    y = 6;
                    break;
                case '8':
                    y = 7;
                    break;
                case 'D':
                    y = 8;
                    isDoor = true;
                    break;
                case 'V':
                    y = 9;
                    isDoor = true;
                    break;
                case 'W':
                    y = 10;
                    isDoor = true;
                    break;
                case 'X':
                    y = 11;
                    isDoor = true;
                    break;
                case 'Y':
                    y = 12;
                    isDoor = true;
                    break;
                case 'Z':
                    y = 13;
                    isDoor = true;
                    break;
                }
                Wall* wall;
                if (isDoor) wall = new Door(sf::Vector2f((float)indexY, (float)indexX), 4, y, 0.1, false, isSecretPassage);
                else wall = new Wall(sf::Vector2f((float)indexY, (float)indexX), nbFrames, y, 0.3, true);
                entityMap[indexY][indexX] = wall;
                entities.push_back(wall);
            }
            else if (map[indexX][indexY] == 'd') {
                Key* key = new Key(sf::Vector2f((float)indexY, (float)indexX), new AnimatedVertexArray("../PoutineStyle/pics/key.png", 64, 64, 0, 1), 'D');
                entityMap[indexY][indexX] = key;
                entities.push_back(key);
            }
            else if (map[indexX][indexY] == 'v') {
                Key* key = new Key(sf::Vector2f((float)indexY, (float)indexX), new AnimatedVertexArray("../PoutineStyle/pics/key.png", 64, 64, 1, 1), 'V');
                entityMap[indexY][indexX] = key;
                entities.push_back(key);
            }
            else if (map[indexX][indexY] == 'w'){
                Key* key = new Key(sf::Vector2f((float)indexY, (float)indexX), new AnimatedVertexArray("../PoutineStyle/pics/key.png", 64, 64, 2, 1), 'W');
                entityMap[indexY][indexX] = key;
                entities.push_back(key);
            }
            else if (map[indexX][indexY] == 'x') {
                Key* key = new Key(sf::Vector2f((float)indexY, (float)indexX), new AnimatedVertexArray("../PoutineStyle/pics/key.png", 64, 64, 3, 1), 'X');
                entityMap[indexY][indexX] = key;
                entities.push_back(key);
            }
            else if (map[indexX][indexY] == 'y') {
                Key* key = new Key(sf::Vector2f((float)indexY, (float)indexX), new AnimatedVertexArray("../PoutineStyle/pics/key.png", 64, 64, 4, 1), 'Y');
                entityMap[indexY][indexX] = key;
                entities.push_back(key);
            }
            else if (map[indexX][indexY] == 'z'){
                Key* key = new Key(sf::Vector2f((float)indexY, (float)indexX), new AnimatedVertexArray("../PoutineStyle/pics/key.png", 64, 64, 5, 1), 'Z');
                entityMap[indexY][indexX] = key;
                entities.push_back(key);
            }
            else if (map[indexX][indexY] == 'S') {
                Portal* portal = new Portal(sf::Vector2f((float)indexY, (float)indexX));
                entityMap[indexY][indexX] = portal;
                entities.push_back(portal);
            }
            else if (map[indexX][indexY] == 'L') {
                rnd = (rand() % 5); // Between 0 and 2
                Entity* entity;
                switch (rnd)
                {
                case 0:
                    entity = new Ammo(sf::Vector2f((float)indexY, (float)indexX));
                    entityMap[indexY][indexX] = entity;
                    entities.push_back(entity);
                    break;
                case 1:
                    entity = new Medikit(sf::Vector2f((float)indexY, (float)indexX));
                    entityMap[indexY][indexX] = entity;
                    entities.push_back(entity);
                    break;
                case 2:
                    entity = new Pistol();
                    entity->mapPos = sf::Vector2f((float)indexY, (float)indexX);
                    entityMap[indexY][indexX] = entity;
                    entities.push_back(entity);
                    break;
                case 3:
                    entity = new Shotgun();
                    entity->mapPos = sf::Vector2f((float)indexY, (float)indexX);
                    entityMap[indexY][indexX] = entity;
                    entities.push_back(entity);
                    break;
                case 4:
                    entity = new GrenadeLauncher();
                    entity->mapPos = sf::Vector2f((float)indexY, (float)indexX);
                    entityMap[indexY][indexX] = entity;
                    entities.push_back(entity);
                    break;
                }
            }
            else
            {
                entityMap[indexY][indexX] = nullptr;
            }
            indexY++;
        }
        indexX++;
        indexY = 0;
    }
    mapFile.close();
}

void StatePlayGame::setHud()
{
    hudUp = new sf::RectangleShape();
    hudDownL = new sf::RectangleShape();
    hudDownML = new sf::RectangleShape();
    hudDownM = new sf::RectangleShape();
    hudDownMR = new sf::RectangleShape();
    hudDownR = new sf::RectangleShape();

    float hudDownWidth = 1.f * (gameManager->getWindowWidth() / 5) - 3;

    sf::Color lineCol = sf::Color::Red;
    sf::Color hudBack = sf::Color::White;

    hudUp->setSize(sf::Vector2f(gameManager->getWindowWidth(), gameManager->getWindowHeight() / 25));
    hudDownL->setSize(sf::Vector2f(hudDownWidth, gameManager->getWindowHeight() / 10));
    hudDownML->setSize(sf::Vector2f(hudDownWidth, gameManager->getWindowHeight() / 10));
    hudDownM->setSize(sf::Vector2f(hudDownWidth, gameManager->getWindowHeight() / 10));
    hudDownMR->setSize(sf::Vector2f(hudDownWidth, gameManager->getWindowHeight() / 10));
    hudDownR->setSize(sf::Vector2f(hudDownWidth, gameManager->getWindowHeight() / 10));

    hudUp->setFillColor(hudBack);
    hudUp->setOutlineColor(lineCol);
    hudUp->setOutlineThickness(3);
    hudUp->setPosition(0, 0);

    hudDownL->setFillColor(hudBack);
    hudDownL->setOutlineColor(lineCol);
    hudDownL->setOutlineThickness(3);
    hudDownL->setPosition(3, gameManager->getWindowHeight() - gameManager->getWindowHeight() / 10 - 3);

    hudDownML->setFillColor(hudBack);
    hudDownML->setOutlineColor(lineCol);
    hudDownML->setOutlineThickness(3);
    hudDownML->setPosition(hudDownWidth + 3, gameManager->getWindowHeight() - gameManager->getWindowHeight() / 10 - 3);

    hudDownM->setFillColor(hudBack);
    hudDownM->setOutlineColor(lineCol);
    hudDownM->setOutlineThickness(3);
    hudDownM->setPosition(hudDownWidth * 2 + 6, gameManager->getWindowHeight() - gameManager->getWindowHeight() / 10 - 3);

    hudDownMR->setFillColor(hudBack);
    hudDownMR->setOutlineColor(lineCol);
    hudDownMR->setOutlineThickness(3);
    hudDownMR->setPosition(hudDownWidth * 3 + 9, gameManager->getWindowHeight() - gameManager->getWindowHeight() / 10 - 3);

    hudDownR->setFillColor(hudBack);
    hudDownR->setOutlineColor(lineCol);
    hudDownR->setOutlineThickness(3);
    hudDownR->setPosition(hudDownWidth * 4 + 12, gameManager->getWindowHeight() - gameManager->getWindowHeight() / 10 - 3);
}

void StatePlayGame::displayHud()
{
    // Draw static stuff
    gameManager->getRenderWindow()->draw(*hudUp);
    gameManager->getRenderWindow()->draw(*hudDownL);
    gameManager->getRenderWindow()->draw(*hudDownML);
    gameManager->getRenderWindow()->draw(*hudDownM);
    gameManager->getRenderWindow()->draw(*hudDownMR);
    gameManager->getRenderWindow()->draw(*hudDownR);

    float widthPos = 1.f;
    float hudDownWidth = widthPos * (gameManager->getWindowWidth() / 5) - 3;
    float heightPos = gameManager->getWindowHeight() / gameManager->getWindowHeight();

    sf::Font font = gameManager->getFont();
    sf::Color fontCol = sf::Color::Red;

    sf::Text liveText("Live : ", font, 15);
    sf::Text live("", font, 15);
    live.setString(std::to_string(player->getLive()));
    sf::Text health("Health :", font, 15);
    sf::RectangleShape visualHealth;
    sf::Text arme("Weapon", font, 15);
    sf::Text ammunition("Ammo :", font, 15);
    sf::Text currentAmmunition("", font, 15);
    currentAmmunition.setString(std::to_string(player->getCurrentAmmunition()) + " / " + std::to_string(player->getAmmunition()));
    sf::Text score("Score :", font, 15);
    sf::Text currentScore("", font, 15);
    currentScore.setString(std::to_string(player->getScore()));

    liveText.setFillColor(fontCol);
    liveText.setPosition(sf::Vector2f(5, gameManager->getWindowHeight() - heightPos * 50));

    live.setFillColor(fontCol);
    live.setPosition(sf::Vector2f(5, gameManager->getWindowHeight() - heightPos * 25));

    health.setFillColor(fontCol);
    health.setPosition(sf::Vector2f(hudDownWidth+6, gameManager->getWindowHeight() - heightPos * 50));

    if (player->getHealth() <= 0)
    {
        visualHealth.setSize(sf::Vector2f(1, 25));
    }
    else
    {
        visualHealth.setSize(sf::Vector2f((hudDownWidth / 100) * player->getHealth(), 25));
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
    gameManager->getRenderWindow()->draw(arme); //TODO remplacere le text par une image de l'arme utilisé
    gameManager->getRenderWindow()->draw(ammunition);
    gameManager->getRenderWindow()->draw(currentAmmunition);
    gameManager->getRenderWindow()->draw(score);
    gameManager->getRenderWindow()->draw(currentScore);
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

void StatePlayGame::cleanAllEntitys()
{
    for (int i = 0; i < this->mapSize; i++)
    {
        for (int j = 0; j < this->mapSize; j++)
        {
            Entity* entity = entityMap[i][j];
            if (entity != nullptr)
            {
                this->entities.remove(entity);
                delete entity;
                entity = nullptr;
                entityMap[i][j] = nullptr;
            }
        }
    }

    this->entities.clear();
}

/// <summary>
/// Get the entity facing the player (1 block away max), otherwise nullptr
/// </summary>
/// <returns>Return * Entity or nullptr</returns>
Entity* StatePlayGame::getInteractedEntity() {
    int playerDirectionPosX = floor(player->position.x + 1.0 * player->direction.x);
    int playerDirectionPosY = floor(player->position.y + 1.0 * player->direction.y);
    if (playerDirectionPosX > 0 && playerDirectionPosX < mapSize && playerDirectionPosY > 0 && playerDirectionPosY < mapSize) {
        if (this->entityMap[playerDirectionPosX][playerDirectionPosY] != nullptr) return entityMap[playerDirectionPosX][playerDirectionPosY];
    }
    return nullptr;
}

void StatePlayGame::bulletExplosion(int nextX, int nextY, int damage) {
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            int newX = nextX + x;
            int newY = nextY + y;
            if (newX > 0 && newX < mapSize - 1 && newY > 0 && newY < mapSize - 1) {
                Entity* entity = entityMap[newX][newY];
                if (entity != nullptr) {
                    if (typeid(*entity).name() == typeid(Guard).name() || typeid(*entity).name() == typeid(General).name()) { // Ennemy
                        Ennemy* ennemy = static_cast<Ennemy*>(entity);
                        ennemy->decreaseHP(damage);
                        // Check if the ennemy is dead
                        if (ennemy->getHP() <= 0) {
                            ennemy->setIsDying();
                        }
                    }
                    else if (entity->getIsDestructible()) {
                        // Remove the entity
                        entityMap[newX][newY] = nullptr;
                        entities.remove(entity);
                        delete entity; entity = nullptr;
                        map[newY][newX] = '0';
                    }
                }
            }
        }
    }
}