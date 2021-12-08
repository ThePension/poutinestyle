#include "StateMainMenu.h"
StateMainMenu::StateMainMenu(GameManager * game) {
	this->gameManager = game;

	// Create buttons
	int w = gameManager->getWindowWidth();
	int h = gameManager->getWindowHeight();

	playButton = Button(sf::Vector2i(w / 2 - 75, 1*(h / 4) - 25), 150, 50, sf::Color::Cyan, L"Jouer", gameManager->getRenderWindow());
	settingsButton = Button(sf::Vector2i(w / 2 - 75, 2 * (h / 4) - 25), 150, 50, sf::Color::Cyan, L"Parametres", gameManager->getRenderWindow());
	quitButton = Button(sf::Vector2i(w / 2 - 75, 3 * (h / 4) - 25), 150, 50, sf::Color::Cyan, L"Quitter", gameManager->getRenderWindow());

	this->btnLevel = Button(sf::Vector2i(w / 2 - 200, 1 * (h / 7) - 25), 120, 50, sf::Color::Cyan, L"Niveaux", gameManager->getRenderWindow());
	this->btnMetaData = Button(sf::Vector2i(w / 2 - 200, 2 * (h / 7) - 25), 120, 50, sf::Color::Cyan, L"MetaData", gameManager->getRenderWindow());
	this->btnSensibility = Button(sf::Vector2i(w / 2 - 200, 3 * (h / 7) - 25), 120, 50, sf::Color::Cyan, L"Sensibilite", gameManager->getRenderWindow());
	this->btnDifficulty = Button(sf::Vector2i(w / 2 - 200, 4 * (h / 7) - 25), 120, 50, sf::Color::Cyan, L"Difficulte", gameManager->getRenderWindow());
	this->btnVolume = Button(sf::Vector2i(w / 2 - 200, 5 * (h / 7) - 25), 120, 50, sf::Color::Cyan, L"Volume", gameManager->getRenderWindow());
}
StateMainMenu::~StateMainMenu() {

}
void StateMainMenu::handleInput(double deltatime) {
	sf::Event event;
	while (gameManager->getRenderWindow()->pollEvent(event))
	{
		if (this->settingsMode)
		{
			if (quitButton.isClicked())
			{
				this->quitButton = Button(sf::Vector2i(gameManager->getWindowWidth() / 2 - 75, 3 * (gameManager->getWindowHeight() / 4) - 25), 150, 50, sf::Color::Cyan, L"Quitter", gameManager->getRenderWindow());
				this->settingsMode = false;
			}
			else if (btnLevel.isClicked())
			{
				// TODO
			}
			else if (btnMetaData.isClicked())
			{
				// TODO
			}
			else if (btnSensibility.isClicked())
			{
				// TODO
			}
			else if (btnDifficulty.isClicked())
			{
				// TODO
			}
			else if (btnVolume.isClicked())
			{
				// TODO
			}
		}
		else
		{
			if (playButton.isClicked()) {
				StatePlayGame* statePlayGame = new StatePlayGame(this->gameManager);
				this->gameManager->changeState(statePlayGame);
				return;
			}
			else if (settingsButton.isClicked()) {
				this->settingsMode = true;
				this->quitButton = Button(sf::Vector2i(gameManager->getWindowWidth() / 2 - 75, 6 * (gameManager->getWindowHeight() / 7)), 150, 50, sf::Color::Cyan, L"Enregistrer", gameManager->getRenderWindow());
			}
			else if (quitButton.isClicked())
			{
				// Quit application
				exit(0);
			}
		}		
	}
}
void StateMainMenu::update(float deltaTime) {
	draw(deltaTime);
	handleInput(deltaTime);
}
void StateMainMenu::draw(double deltatime) {
	if (this->settingsMode)
	{
		btnLevel.draw();
		btnMetaData.draw();
		btnSensibility.draw();
		btnDifficulty.draw();
		btnVolume.draw();

		showSettingsLabel();
	}
	else
	{
		playButton.draw();
		settingsButton.draw();
	}

	quitButton.draw();
}

void StateMainMenu::showSettingsLabel()
{
	int wAlign = gameManager->getWindowWidth() / 2 - 50;
	int hAlign = gameManager->getWindowHeight() / 7;

	sf::Font font = gameManager->getFont();

	sf::Text pause = sf::Text("A completer ...", font, 15);
	pause.setFillColor(sf::Color::White);
	pause.setPosition(sf::Vector2f(wAlign, 1 * hAlign - 7));
	gameManager->getRenderWindow()->draw(pause);

	sf::Text pause0 = sf::Text("A completer ...", font, 15);
	pause.setFillColor(sf::Color::White);
	pause.setPosition(sf::Vector2f(wAlign, 2 * hAlign - 7));
	gameManager->getRenderWindow()->draw(pause);

	sf::Text pause1 = sf::Text("A completer ...", font, 15);
	pause.setFillColor(sf::Color::White);
	pause.setPosition(sf::Vector2f(wAlign, 3 * hAlign - 7));
	gameManager->getRenderWindow()->draw(pause);

	sf::Text pause2 = sf::Text("A completer ...", font, 15);
	pause.setFillColor(sf::Color::White);
	pause.setPosition(sf::Vector2f(wAlign, 4 * hAlign - 7));
	gameManager->getRenderWindow()->draw(pause);

	sf::Text pause3 = sf::Text("A completer ...", font, 15);
	pause.setFillColor(sf::Color::White);
	pause.setPosition(sf::Vector2f(wAlign, 5 * hAlign - 7));
	gameManager->getRenderWindow()->draw(pause);
}


