#include "StatePlayGame.h"
StatePlayGame::StatePlayGame(GameManager* game)
{
    this->gameManager = game;

    map = new int*[mapSize];
    for (int i = 0; i < mapSize; i++)
    {
        map[i] = new int[mapSize];
        for (int j = 0; j < mapSize; j++)
        {
            map[i][j] = 0;
        }
    }

    mapLocation = mapFileFolder + mapFileName;
	mapFile.open(mapLocation);
	parseMap2D();

    // windowGame.create(sf::VideoMode(gameManager->getWindowWidth(), gameManager->getWindowHeight()), "RayCasting with SFML", sf::Style::None | sf::Style::Titlebar | sf::Style::Close);

    blockWidth = gameManager->getWindowWidth() / mapSize;
    blockHeight = gameManager->getWindowHeight() / mapSize;

    block.setSize(sf::Vector2f(blockWidth, blockHeight));
    block.setOutlineThickness(1);
    block.setOutlineColor(sf::Color::Black);

    player_circle.setRadius(10.f);
    player_circle.setPosition(playerPosition);
    player_circle.setFillColor(sf::Color::Green);

    // planeVec = matrixMult(planeVec, -90.f * 3.1415 / 180.f);
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

        /*if (event.type == sf::Event::MouseMoved)
        {
            std::cout << "new mouse x: " << event.mouseMove.x << std::endl;
            std::cout << "new mouse y: " << event.mouseMove.y << std::endl;
        }*/

        if (event.type == sf::Event::KeyPressed)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) isMapDisplayed = !isMapDisplayed; // Toggle map display
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                // Move the player position (forward) depending on player direction
                playerPosition.x += playerDir.x * 5; // 5 is a random value, should be a constant
                playerPosition.y += playerDir.y * 5;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                playerDir = matrixMult(playerDir, -0.1); // Rotate the player direction
                planeVec = matrixMult(planeVec, -0.1); // Rotate plane direction
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                // Move the player position (backward) depending on player direction
                playerPosition.x -= playerDir.x * 5; // 5 is a random value, should be a constant
                playerPosition.y -= playerDir.y * 5;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                playerDir = matrixMult(playerDir, 0.1); // Rotate the player direction
                planeVec = matrixMult(planeVec, 0.1); // Rotate plane direction
            }
        }
    }

    player_circle.setPosition(playerPosition);    
}
void StatePlayGame::update()
{
    handleInput();
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

            if (map[i][j] == 1) // needs a fastest way to test if there's more cases. [ O(n^2) ]
            {
                block.setFillColor(sf::Color::Red);
            }
            else
            {
                block.setFillColor(sf::Color::Black);
            }

            gameManager->getRenderWindow()->draw(block);
        }
    }
    gameManager->getRenderWindow()->draw(player_circle);

    // Draw player direction vector
    sf::Vertex playerDirLine[] =
    {
        sf::Vertex(playerPosition + sf::Vector2f(player_circle.getRadius(), player_circle.getRadius())),
        sf::Vertex(sf::Vector2f(playerPosition.x + 32 * playerDir.x + player_circle.getRadius(), playerPosition.y + 32 * playerDir.y + player_circle.getRadius()))
    };
    gameManager->getRenderWindow()->draw(playerDirLine, 2, sf::Lines);
}
void StatePlayGame::drawMap3D() {
    // Number of rays (lines drawn on the screen) --> Must be a mutiple of 66
    int w = 660;

    for (int x = 0; x < w; x++) { // FOV of 66 degrees --> 66 rays
        // Cell where the player is standing
        sf::Vector2i playerMapPos = sf::Vector2i(int(playerPosition.x / blockWidth), int(playerPosition.y / blockHeight));

        // Vector representing the direction of the actual ray
        double cameraX = double(2 * x) / double(w) - 1;

        sf::Vector2f rayDir = playerDir + sf::Vector2f(planeVec.x * cameraX, planeVec.y * cameraX);
        double rayDirLen = std::sqrt(pow(rayDir.x, 2) + pow(rayDir.y, 2));

        // Fisheye effect
        // double deltaDistX = (rayDir.x == 0) ? 1e30 : abs(rayDirLen / rayDir.x); 
        // double deltaDistY = (rayDir.y == 0) ? 1e30 : abs(rayDirLen / rayDir.y);

        double deltaDistX = (rayDir.x == 0) ? 1e30 : abs(1 / rayDir.x); // RayDir is a unit vector, length = 1
        double deltaDistY = (rayDir.y == 0) ? 1e30 : abs(1 / rayDir.y);

        double sideDistX, sideDistY;

        int stepX, stepY, side;
        bool wallHit = false;

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
                side = 0;
            }
            else {
                sideDistY += deltaDistY;
                playerMapPos.y += stepY;
                side = 1;
            }
            if (map[playerMapPos.y][playerMapPos.x] == 1) wallHit = true; // Inversion des composantes car sinon rotation de 90° ! Pas compris pourquoi ?
        }
        double perpWallDist;
        if (side == 0) perpWallDist = sideDistX - deltaDistX;
        else perpWallDist = sideDistY - deltaDistY;

        sf::Color wallColor;
        if (side == 1) wallColor = sf::Color::Blue;
        else wallColor = sf::Color::Red;

        int lineHeight = int(gameManager->getWindowHeight() / perpWallDist);

        int drawStart = -lineHeight / 2 + gameManager->getWindowHeight() / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + gameManager->getWindowHeight() / 2;
        if (drawEnd >= gameManager->getWindowHeight()) drawEnd = gameManager->getWindowHeight() - 1;

        sf::ConvexShape line;
        line.setPointCount(4);
        double lineW = gameManager->getWindowWidth() / double(w);
        line.setPoint(0, sf::Vector2f(x * lineW, drawStart));
        line.setPoint(1, sf::Vector2f(x * lineW + lineW, drawStart));
        line.setPoint(3, sf::Vector2f(x * lineW, drawEnd));
        line.setPoint(2, sf::Vector2f(x * lineW + lineW, drawEnd));

        line.setFillColor(wallColor);

        gameManager->getRenderWindow()->draw(line);

        // Draw rays
        /*sf::Vertex ray[] =
        {
            sf::Vertex(playerPosition),
            sf::Vertex(sf::Vector2f(double(playerMapPos.x * blockWidth), double(playerMapPos.y * blockWidth)))
        };
        windowGame.draw(ray, 2, sf::Lines);*/
    }
}

void StatePlayGame::parseMap2D()
{
    while (std::getline(mapFile, tempText))
    {
        for (auto it = tempText.cbegin(); it != tempText.cend(); ++it)
        {
            if (*it == '1')
            {
                map[indexX][indexY] = 1;
            }
            indexY++;
        }
        indexX++;
        indexY = 0;
    }

    mapFile.close();
}
