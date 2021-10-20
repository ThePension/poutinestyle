#include "StatePlayGame.h"
StatePlayGame::StatePlayGame()
{
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

    windowGame.create(sf::VideoMode(windowWidth, windowHeight), "RayCasting with SFML", sf::Style::None | sf::Style::Titlebar | sf::Style::Close);

    blockWidth = windowWidth / mapSize;
    blockHeight = windowHeight / mapSize;

    block.setSize(sf::Vector2f(blockWidth, blockHeight));
    block.setOutlineThickness(1);
    block.setOutlineColor(sf::Color::Black);

    player_circle.setRadius(10.f);
    player_circle.setPosition(playerPosition);
    player_circle.setFillColor(sf::Color::Green);
}
sf::Vector2f StatePlayGame::matrixMult(sf::Vector2f v, double a) {
    // Rotation matrix (used
    // [cosa  -sina]
    // [sina   cosa]
    sf::Vector2f resVec = sf::Vector2f();
    resVec.x = v.x * cos(a) - v.y * sin(a);
    resVec.y = v.x * sin(a) + v.y * cos(a);

    // Need a unit vector --> Divide component by length of the vector
    double vecLen = sqrt(pow(resVec.x, 2) + pow(resVec.y, 2));
    resVec.x /= vecLen;
    resVec.y /= vecLen;
    return resVec;
}
StatePlayGame::~StatePlayGame() {

}
void StatePlayGame::handleInput()
{
    while (windowGame.isOpen())
    {
        sf::Event event;
        while (windowGame.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                windowGame.close();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                {
                    // Move the player position (forward) depending on player direction
                    playerPosition.x += playerDir.x * 5; // 5 is a random value, should be a constant
                    playerPosition.y += playerDir.y * 5;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {
                    playerDir = matrixMult(playerDir, -0.1); // Change the player direction
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                {
                    // Move the player position (backward) depending on player direction
                    playerPosition.x -= playerDir.x * 5; // 5 is a random value, should be a constant
                    playerPosition.y -= playerDir.y * 5;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                {
                    playerDir = matrixMult(playerDir, 0.1); // Change the player direction
                }
            }
        }

        player_circle.setPosition(playerPosition);

        draw();
    }
}
void StatePlayGame::update()
{
    handleInput();
    // draw();
}
void StatePlayGame::draw()
{
    windowGame.clear();
    drawMap2D();
    // drawMap3D();
    windowGame.display();
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
                block.setFillColor(sf::Color::White);
            }

            windowGame.draw(block);
        }
    }

    /*for (int r = 0; r < 60; r++) { // FOV of 60 degrees --> 60 rays
        sf::Vector2f pos(player_circle.getPosition().x, player_circle.getPosition().y);
        sf::Vector2f dir;
        sf::Vector2f plane;        
    }*/

    windowGame.draw(player_circle);
}
void StatePlayGame::drawMap3D() {
    
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
