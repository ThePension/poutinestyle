#include "StateGameOverMenu.h"
StateGameOverMenu::StateGameOverMenu(GameManager* game) {
	this->gameManager = game;

	// Create buttons
	replayButton = Button(sf::Vector2i(150, 800), 300, 100, sf::Color::Cyan, L"Rejouer", gameManager->getRenderWindow());
	quitButton = Button(sf::Vector2i(550, 800), 300, 100, sf::Color::Cyan, L"Quitter", gameManager->getRenderWindow());
}
StateGameOverMenu::~StateGameOverMenu() {

}
void StateGameOverMenu::handleInput(double deltatime) {
	sf::Event event;
	while (gameManager->getRenderWindow()->pollEvent(event))
	{
		if (replayButton.isClicked() && !isReplayClicked) {
			StatePlayGame* statePlayGame = new StatePlayGame(this->gameManager); // Create new PlayGame state
			gameManager->changeState(statePlayGame); // Change current state for new PlayGame state
			isReplayClicked = true;
			return;
		}
		else if (quitButton.isClicked()) {
			// Quit application
			exit(0);
		}
	}
}
void StateGameOverMenu::update(float deltaTime) {
	handleInput(deltaTime);
	if(!isReplayClicked) draw(deltaTime);
}
void StateGameOverMenu::draw(double deltatime) {
	this->gameManager->getRenderWindow()->clear();
	replayButton.draw();
	quitButton.draw();
	this->gameManager->getRenderWindow()->display();
}
