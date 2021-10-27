#include "GameManager.h"

// Needed here to avoid circular dependency
#include "GameState.h"
#include "StatePlayGame.h"
#include "StateMainMenu.h"
#include "StatePauseMenu.h"

GameManager::GameManager()
{
    window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), "RayCasting with SFML", sf::Style::None | sf::Style::Titlebar | sf::Style::Close);
    StateMainMenu* stateMainMenu = new StateMainMenu(this);
    states.push(stateMainMenu);
}

void GameManager::gameLoop()
{
    while (window->isOpen())
    {
        if (peekState() == nullptr) continue;
        peekState()->update();
    }
}

void GameManager::pushState(GameState* state) {
    if (peekState() != nullptr) {
        // Can't stack two states with with same type in a row
        this->states.push(state);
    }
}
void GameManager::popState() {
    delete this->states.top();
    this->states.pop();
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
bool GameManager::containsState(GameState* state) {
    if (peekState() != nullptr) {
        // Can't stack two same states in a row
        return typeid(*state).name() == typeid(*peekState()).name();
    }
}
