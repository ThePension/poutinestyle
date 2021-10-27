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
	if (playButton.isClicked()) {
		std::cout << "Jouer" << std::endl;
	}
	else if (settingsButton.isClicked()) {
		std::cout << "Paramètres" << std::endl;
	}
	else if (quitButton.isClicked()) {
		std::cout << "Quitter" << std::endl;
	}
}
void StateMainMenu::update() {
	handleInput();

	draw();
}
void StateMainMenu::draw() {
	this->gameManager->getRenderWindow()->clear();
	playButton.draw();
	settingsButton.draw();
	quitButton.draw();
	this->gameManager->getRenderWindow()->display();
}
