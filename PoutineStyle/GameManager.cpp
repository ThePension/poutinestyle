#include "GameManager.h"

// Needed here to avoid circular dependency
#include "GameState.h"
#include "StatePlayGame.h"
#include "StateMainMenu.h"
#include "StatePauseMenu.h"
#include "StateGameOverMenu.h"

GameManager::GameManager()
{
    window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), "RayCasting with SFML", sf::Style::None | sf::Style::Titlebar | sf::Style::Close);

    StateMainMenu* stateMainMenu = new StateMainMenu(this);
    states.push(stateMainMenu);

    window->setPosition(sf::Vector2i(500, 0));
}

void GameManager::gameLoop()
{
    while (window->isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        if (peekState() != nullptr) peekState()->update(deltaTime);
    }
}

void GameManager::pushState(GameState* state) {
    if (peekState() == nullptr) {
        this->states.push(state);
    }
}

void GameManager::popState() {
    if (!this->states.empty()) {
        GameState * stateToDelete = this->states.top();
        delete stateToDelete;
        stateToDelete = nullptr;
        this->states.pop();
    }
}

void GameManager::changeState(GameState* state) {
    if (!this->states.empty()) {
        popState();
    }
    pushState(state);
}

GameState* GameManager::peekState()
{
    if (this->states.empty()) return nullptr;
    else return this->states.top();
}

