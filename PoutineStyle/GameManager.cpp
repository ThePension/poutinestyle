#include "GameManager.h"

// Needed here to avoid circular dependency
#include "GameState.h"
#include "StatePlayGame.h"
#include "StateMainMenu.h"
#include "StatePauseMenu.h"

GameManager::GameManager()
{
    window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), "RayCasting with SFML", sf::Style::None | sf::Style::Titlebar | sf::Style::Close);

    StatePlayGame *statePlayGame = new StatePlayGame(this);
    states.push(statePlayGame);
}

void GameManager::gameLoop()
{
    while (window->isOpen())
    {
        states.top()->update();   
    }
}

void GameManager::pushState(GameState* state) {

}
void GameManager::popState() {

}
void GameManager::changeState(GameState* state) {

}
GameState* GameManager::peekState()
{
    return nullptr;
}
