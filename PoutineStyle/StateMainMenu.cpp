#include "StateMainMenu.h"
StateMainMenu::StateMainMenu(GameManager * game) {
	this->gameManager = game;

	// Create buttons
	int w = gameManager->getWindowWidth();
	int h = gameManager->getWindowHeight();
	playButton = Button(sf::Vector2i(w / 2 - 75, 1*(h / 4) - 25), 150, 50, sf::Color::Cyan, L"Jouer", gameManager->getRenderWindow());
	settingsButton = Button(sf::Vector2i(w / 2 - 75, 2 * (h / 4) - 25), 150, 50, sf::Color::Cyan, L"Paramètres", gameManager->getRenderWindow());
	quitButton = Button(sf::Vector2i(w / 2 - 75, 3 * (h / 4) - 25), 150, 50, sf::Color::Cyan, L"Quitter", gameManager->getRenderWindow());
}
StateMainMenu::~StateMainMenu() {

}
void StateMainMenu::handleInput(double deltatime) {
	sf::Event event;
	while (gameManager->getRenderWindow()->pollEvent(event))
	{
		if (playButton.isClicked()) {
			//StatePlayGame* statePlayGame = new StatePlayGame(this->gameManager, "Tutoriel.txt", 10);
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
	draw(deltaTime);
	handleInput(deltaTime);
}
void StateMainMenu::draw(double deltatime) {
	playButton.draw();
	settingsButton.draw();
	quitButton.draw();
}
