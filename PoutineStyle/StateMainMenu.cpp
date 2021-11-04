#include "StateMainMenu.h"
StateMainMenu::StateMainMenu(GameManager * game) {
	this->gameManager = game;

	// Create buttons
	playButton = Button(sf::Vector2i(350, 200), 300, 100, sf::Color::Cyan, L"Jouer", gameManager->getRenderWindow());
	settingsButton = Button(sf::Vector2i(350, 400), 300, 100, sf::Color::Cyan, L"Paramètres", gameManager->getRenderWindow());
	quitButton = Button(sf::Vector2i(350, 600), 300, 100, sf::Color::Cyan, L"Quitter", gameManager->getRenderWindow());
}
StateMainMenu::~StateMainMenu() {

}
void StateMainMenu::handleInput() {
	sf::Event event;
	while (gameManager->getRenderWindow()->pollEvent(event))
	{
		if (playButton.isClicked()) {
			StatePlayGame* statePlayGame = new StatePlayGame(this->gameManager);
			this->gameManager->changeState(statePlayGame);
			return;
		}
		else if (settingsButton.isClicked()) {
			// To do
		}
		else if (quitButton.isClicked()) {
			// Quit application
			exit(0);
		}
	}
}
void StateMainMenu::update(float deltaTime) {
	draw();
	handleInput();
}
void StateMainMenu::draw() {
	playButton.draw();
	settingsButton.draw();
	quitButton.draw();
}
