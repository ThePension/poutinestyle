#include "GameManager.h"
GameManager::GameManager() {

}

void GameManager::gameLoop() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}

void GameManager::pushState(GameState* state) {

}
void GameManager::popState() {

}
void GameManager::changeState(GameState* state) {

}
GameState* peekState() {
    return nullptr;
}
