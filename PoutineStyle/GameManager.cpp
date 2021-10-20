#include "GameManager.h"
GameManager::GameManager()
{
    StatePlayGame *statePlayGame = new StatePlayGame();
    states.push(statePlayGame);
}

void GameManager::gameLoop()
{
    states.top()->update();
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
