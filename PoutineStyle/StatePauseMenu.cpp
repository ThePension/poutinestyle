#include "StatePauseMenu.h"
#include "StatePlayGame.h"

StatePauseMenu::StatePauseMenu(GameManager* game)
{
	this->gameManager = game;

	w = gameManager->getWindowWidth();
	h = gameManager->getWindowHeight();

	playButton = Button(sf::Vector2i(int(w / 2 - 75), int(1.5 * (h / 4) - 25)), 150, 50, sf::Color::Red, L"Reprendre", gameManager->getRenderWindow());
	backToMainMenu = Button(sf::Vector2i(int(w / 2 - 75), int(2.5 * (h / 4) - 25)), 150, 50, sf::Color::Red, L"Menu principal", gameManager->getRenderWindow());
	quitButton = Button(sf::Vector2i(int(w / 2 - 75), int(3.5 * (h / 4) - 25)), 150, 50, sf::Color::Red, L"Quitter", gameManager->getRenderWindow());
}

StatePauseMenu::~StatePauseMenu() {}

void StatePauseMenu::handleInput(double deltatime)
{
	sf::Event event;
	while (gameManager->getRenderWindow()->pollEvent(event))
	{
		if (playButton.isClicked())
		{
			gameManager->gameMusic->play();
			gameManager->menuMusic->stop();
			StatePlayGame* playGame = dynamic_cast<StatePlayGame*>(this->gameManager->peekState(1));
			playGame->resume();
			this->gameManager->popState();
			return;
		}
		else if (backToMainMenu.isClicked()) {
			StateMainMenu* stateMainMenu = new StateMainMenu(this->gameManager);
			this->gameManager->changeState(stateMainMenu);
			return;
		}
		else if (quitButton.isClicked())
		{
			// Quit application
			exit(0);
		}
	}
}

void StatePauseMenu::update(float deltaTime)
{
	draw(deltaTime);
	handleInput(deltaTime);
}

void StatePauseMenu::draw(double deltaTime)
{
	sf::Font font = gameManager->getFont();

	pause = sf::Text("Pause", font, 35);
	pause.setFillColor(sf::Color::White);
	pause.setPosition(sf::Vector2f(w / 2 - 57.f, 1 * (h / 4) - 25.f));
	gameManager->getRenderWindow()->draw(pause);

	playButton.draw();
	quitButton.draw();
	backToMainMenu.draw();
}
