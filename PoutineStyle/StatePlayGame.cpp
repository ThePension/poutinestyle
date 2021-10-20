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
    player_circle.setPosition(startPosition);
    player_circle.setFillColor(sf::Color::Green);
}
StatePlayGame::~StatePlayGame() {

}
void StatePlayGame::handleInput()
{
    while (windowGame.isOpen())
    {
        sf::Vector2f playerActualPosition = player_circle.getPosition();

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
                    playerActualPosition.y -= deplacement;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {
                    playerActualPosition.x -= deplacement;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                {
                    playerActualPosition.y += deplacement;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                {
                    playerActualPosition.x += deplacement;
                }
            }
        }

        player_circle.setPosition(playerActualPosition);

        draw();
    }
}
void StatePlayGame::update()
{
    handleInput();
}
void StatePlayGame::draw()
{
    windowGame.clear();

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

    windowGame.draw(player_circle);
    windowGame.display();
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
