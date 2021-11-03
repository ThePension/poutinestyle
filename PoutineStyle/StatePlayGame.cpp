#include "StatePlayGame.h"
#include "Sprite.h"
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

    block.setSize(sf::Vector2f(blockWidth, blockHeight));
    block.setOutlineThickness(1);
    block.setOutlineColor(sf::Color::Black);

    player_circle.setRadius(10.f);
    player_circle.setPosition(playerPosition - sf::Vector2f(10, 10));
    player_circle.setFillColor(sf::Color::Green);

    textures = sf::Texture();
    textures.loadFromFile("C:\\users\\nicolas.aubert1\\desktop\\textures.png");
    // https://www.tilingtextures.com/stone-wall-with-mortar/
    spriteTextures = sf::Texture();
    spriteTextures.loadFromFile("C:\\users\\nicolas.aubert1\\desktop\\sprite.png");
}
sf::Vector2f StatePlayGame::matrixMult(sf::Vector2f v, double a) {
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
StatePlayGame::~StatePlayGame() {

}
void StatePlayGame::handleInput()
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
            if (oldMouseX > event.mouseMove.x || event.mouseMove.x == 0) {
                playerDir = matrixMult(playerDir, -0.03); // Rotate the player direction
                planeVec = matrixMult(planeVec, -0.03); // Rotate plane direction
            }
            else if (oldMouseX < event.mouseMove.x || event.mouseMove.x == gameManager->getWindowWidth() - 1) {
                playerDir = matrixMult(playerDir, 0.03); // Rotate the player direction
                planeVec = matrixMult(planeVec, 0.03); // Rotate plane direction
            }
            oldMouseX = event.mouseMove.x;
        }

        if (event.type == sf::Event::KeyPressed)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) isMapDisplayed = !isMapDisplayed; // Toggle map display
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                isPlayerMoving = true;
                keyPressed = sf::Keyboard::W;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                isPlayerMoving = true;
                keyPressed = sf::Keyboard::A;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                isPlayerMoving = true;
                keyPressed = sf::Keyboard::S;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                isPlayerMoving = true;
                keyPressed = sf::Keyboard::D;
            }
        }
        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::A) isPlayerMoving = false;
            if (event.key.code == sf::Keyboard::D) isPlayerMoving = false;
            if (event.key.code == sf::Keyboard::W) isPlayerMoving = false;
            if (event.key.code == sf::Keyboard::S) isPlayerMoving = false;
        }
    }

    player_circle.setPosition(playerPosition - sf::Vector2f(10, 10));
}
void StatePlayGame::update()
{
    handleInput();

    // Player controls
    sf::Vector2f newPlayerPos;
    int newPlayerPosOnMapY, newPlayerPosOnMapX;
    if (isPlayerMoving) {
        switch (keyPressed)
        {
        case sf::Keyboard::A:
            playerDir = matrixMult(playerDir, -0.1); // Rotate the player direction
            planeVec = matrixMult(planeVec, -0.1); // Rotate plane direction
            break;
        case sf::Keyboard::D:
            playerDir = matrixMult(playerDir, 0.1); // Rotate the player direction
            planeVec = matrixMult(planeVec, 0.1); // Rotate plane direction
            break;
        case sf::Keyboard::W:
            // Check wall collision
            newPlayerPos = sf::Vector2f(playerPosition.x + playerDir.x * movingSpeed, playerPosition.y + playerDir.y * movingSpeed);
            newPlayerPosOnMapY = newPlayerPos.x / blockWidth;
            newPlayerPosOnMapX = newPlayerPos.y / blockHeight;
            if (map[newPlayerPosOnMapX][newPlayerPosOnMapY] != '1') {
                // Move the player position (forward) depending on player direction
                playerPosition = newPlayerPos;
            }
            break;
        case sf::Keyboard::S:
            newPlayerPos = sf::Vector2f(playerPosition.x - playerDir.x * movingSpeed, playerPosition.y - playerDir.y * movingSpeed);
            newPlayerPosOnMapY = newPlayerPos.x / blockWidth;
            newPlayerPosOnMapX = newPlayerPos.y / blockHeight;
            if (map[newPlayerPosOnMapX][newPlayerPosOnMapY] != '1') {
                // Move the player position (backward) depending on player direction
                playerPosition = newPlayerPos;
            }
            break;
        }
    }

    draw();
}
void StatePlayGame::draw()
{
    gameManager->getRenderWindow()->clear();
    if(isMapDisplayed) drawMap2D();
    else drawMap3D();
    gameManager->getRenderWindow()->display();
}

void StatePlayGame::drawMap2D() {
    for (int i = 0; i < mapSize; i++)
    {
        for (int j = 0; j < mapSize; j++)
        {
            block.setPosition(j * blockWidth, i * blockHeight);

            if (map[i][j] == '1') // needs a fastest way to test if there's more cases. [ O(n^2) ]
            {
                block.setFillColor(sf::Color::Red);
            }
            else if(map[i][j] == '0')
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
        sf::Vertex(playerPosition),
        sf::Vertex(sf::Vector2f(playerPosition.x + 32 * playerDir.x, playerPosition.y + 32 * playerDir.y))
    };
    gameManager->getRenderWindow()->draw(playerDirLine, 2, sf::Lines);
}
void StatePlayGame::drawMap3D() {
    // Number of rays (vertical lines drawn on the screen) --> Must be a multiple of 66
    int w = gameManager->getWindowWidth();
    sf::VertexArray lines(sf::Lines, 2*gameManager->getWindowWidth()); // Must be bigger if we want to draw floors and ceilings
    std::vector<Sprite> spritesArray = std::vector<Sprite>();
    sf::VertexArray spritesVertex(sf::Lines, 2*gameManager->getWindowWidth());
    for (int x = 0; x < w; x++) { // FOV of 66 degrees --> 66 rays
        // Cell where the player is standing
        sf::Vector2i playerMapPos = sf::Vector2i(int(playerPosition.x / blockWidth), int(playerPosition.y / blockHeight));

        // Vector representing the direction of the actual ray
        double cameraX = double(2.f * x) / double(w) - 1;

        sf::Vector2f rayDir = playerDir + sf::Vector2f(planeVec.x * cameraX, planeVec.y * cameraX);
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
            sideDistX = ((playerPosition.x / blockHeight) - double(playerMapPos.x)) * deltaDistX;
        }
        else {
            stepX = 1;
            sideDistX = (double(playerMapPos.x) + 1.f - (playerPosition.x / blockHeight)) * deltaDistX;
        }
        if (rayDir.y < 0) {
            stepY = -1;
            sideDistY = ((playerPosition.y / blockHeight) - double(playerMapPos.y)) * deltaDistY;
        }
        else {
            stepY = 1;
            sideDistY = (double(playerMapPos.y) + 1.f - (playerPosition.y / blockHeight)) * deltaDistY;
        }

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
            if (map[playerMapPos.y][playerMapPos.x] == '1') wallHit = true; // Inversion des composantes car sinon rotation de 90° ! Pas compris pourquoi ?
            else if (map[playerMapPos.y][playerMapPos.x] == 'E') {
                bool isContained = false;
                for(Sprite const& s : spritesArray) {
                    if (s.mapX == playerMapPos.x && s.mapY == playerMapPos.y) isContained = true;
                }
                if (!isContained) {
                    // std::cout << "True" << std::endl;
                    Sprite sprite = Sprite();
                    sprite.distance = sideDistX - deltaDistX;
                    sprite.type = 'E';
                    sprite.mapX = playerMapPos.x;
                    sprite.mapY = playerMapPos.y;
                    spritesArray.push_back(sprite);
                }
            }
        }
        double perpWallDist;
        if (isWallHitHorizontal) perpWallDist = sideDistX - deltaDistX;
        else perpWallDist = sideDistY - deltaDistY;

        sf::Color wallColor;
        if (isWallHitHorizontal) wallColor = sf::Color::White;
        else wallColor = sf::Color(126, 126, 126);

        int lineHeight = int(gameManager->getWindowHeight() / perpWallDist);

        int drawStart = -lineHeight / 2 + gameManager->getWindowHeight() / 2;
        int drawEnd = lineHeight / 2 + gameManager->getWindowHeight() / 2;

        // Texture stuff
        int wallTextureNum = 0; // Need to be set depending on wall type (char)
        sf::Vector2i texture_coords(
            wallTextureNum * textureSize,
            0 // For the moment, all textures are on the same line (y coord) in textures.png file
        );

        // Calculate where the wall was hit
        float wallX;
        if (isWallHitHorizontal) wallX = (playerPosition.y / blockHeight) + perpWallDist * rayDir.y;
        else wallX = (playerPosition.x / blockWidth) + perpWallDist * rayDir.x;
        wallX -= floor(wallX);

        // Get x coordinate on the wall texture
        int texX = int(wallX * float(textureSize));
        if ((isWallHitHorizontal && rayDir.x > 0) || (!isWallHitHorizontal && rayDir.y < 0))
            texX = textureSize - texX - 1;

        texture_coords.x += texX;

        // Adding vertical lines in ArrayVertex, and set the coordinates of the texture to use
        // x * 2 are all the first points of the lines (top ones) (more info there : https://www.sfml-dev.org/tutorials/2.5/graphics-vertex-array.php)
        lines[x * 2].position = sf::Vector2f((float)x, (float)drawStart);
        lines[x * 2].color = wallColor;
        lines[x * 2].texCoords = sf::Vector2f((float)texture_coords.x, (float)texture_coords.y + 1);
        // x * 2 + 1 are all the seconds points of the lines (bottom ones)
        lines[x * 2 + 1].position = sf::Vector2f((float)x, (float)drawEnd);
        lines[x * 2 + 1].color = wallColor;
        lines[x * 2 + 1].texCoords = sf::Vector2f((float)texture_coords.x, (float)(texture_coords.y + textureSize - 1));

        ZBuffer[x] = perpWallDist; // Needed with sprite rendering
    }

    // Rendering sprites stuff
    // To do : Sort sprites in spritesArray

    // Sprites Projection
    for (int i = 0; i < spritesArray.size(); i++) {
        Sprite sprite = spritesArray.at(i);

        // Translate sprite pos relative to the camera
        double spriteX = (double)sprite.mapX - playerPosition.x / (double)blockWidth;
        spriteX += 0.5; // Center the sprite in the cell
        double spriteY = (double)sprite.mapY - playerPosition.y / (double)blockHeight;
        spriteY += 0.5; // Center the sprite in the cell

        // Projection values
        double invDet = 1.0 / ((double)planeVec.x * (double)playerDir.y - (double)playerDir.x * (double)planeVec.y);

        double transformX = invDet * (playerDir.y * spriteX - playerDir.x * spriteY);
        double transformY = invDet * (-planeVec.y * spriteX + planeVec.x * spriteY);

        int spriteScreenX = int((w / 2) * (1 + transformX / transformY));
        int h = gameManager->getWindowHeight();
        int spriteHeight = abs(int(h / transformY)) - 32;

        // Where the sprite should be displayed (on screen y coordinates)
        int drawStartY = -spriteHeight / 2 + h / 2;
        int drawEndY = spriteHeight / 2 + h / 2;

        //calculate width of the sprite
        int spriteWidth = abs(int(h / (transformY))) - 32;

        // Where the sprite should be displayed (on screen x coordinates)
        int drawStartX = -spriteWidth / 2 + spriteScreenX;
        if (drawStartX < 0) drawStartX = 0;
        int drawEndX = spriteWidth / 2 + spriteScreenX;
        if (drawEndX >= w) drawEndX = w - 1;

        for (int j = drawStartX; j < drawEndX; j++) {
            // X coordinates of the sprite on the texture (y is useless, because it's always 0)
            int texX = int(256 * (j - (-spriteWidth / 2 + spriteScreenX)) * textureSize / spriteWidth) / 256;

            if (transformY < ZBuffer[j]) {
                // Adding vertical lines in ArrayVertex, and set the coordinates of the texture to use
                // x * 2 are all the first points of the lines (top ones) (more info there : https://www.sfml-dev.org/tutorials/2.5/graphics-vertex-array.php)
                spritesVertex[j * 2].position = sf::Vector2f((float)j, (float)drawStartY + abs(drawStartY - drawEndY) / 2);
                spritesVertex[j * 2].color = sf::Color::White;
                spritesVertex[j * 2].texCoords = sf::Vector2f((float)texX, (float)1);
                // x * 2 + 1 are all the seconds points of the lines (bottom ones)
                spritesVertex[j * 2 + 1].position = sf::Vector2f((float)j, (float)drawEndY + abs(drawStartY - drawEndY) / 2);
                spritesVertex[j * 2 + 1].color = sf::Color::White;
                spritesVertex[j * 2 + 1].texCoords = sf::Vector2f((float)texX, (float)(0 + textureSize - 1));
            }
        }
    }
    // Clean the spritesArray
    spritesArray.clear();

    // Draw walls with textures
    gameManager->getRenderWindow()->draw(lines, &textures);

    // Draw sprites
    gameManager->getRenderWindow()->draw(spritesVertex, &spriteTextures);
}

void StatePlayGame::parseMap2D()
{
    std::string tempText;
    std::ifstream mapFile;
    std::string mapLocation = mapFileFolder + mapFileName;
    mapFile.open(mapLocation);

    int indexX = 0, indexY = 0;
    while (std::getline(mapFile, tempText))
    {
        for (auto it = tempText.cbegin(); it != tempText.cend(); ++it)
        {
            map[indexX][indexY] = *it;
            if (map[indexX][indexY] == 'T') // Player spawn position
            {
                playerPosition = sf::Vector2f(indexY * blockWidth + blockWidth / 2, indexX * blockHeight + blockHeight / 2);
            }
            indexY++;
        }
        indexX++;
        indexY = 0;
    }

    mapFile.close();
}
