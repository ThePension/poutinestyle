#include "StatePauseMenu.h"
#include "StatePlayGame.h"

StatePauseMenu::StatePauseMenu(GameManager* game)
{
	this->gameManager = game;

	w = gameManager->getWindowWidth();
	h = gameManager->getWindowHeight();

	playButton = Button(sf::Vector2i(w / 2 - 75, 2 * (h / 4) - 25), 150, 50, sf::Color::Cyan, L"Reprendre", gameManager->getRenderWindow());
	quitButton = Button(sf::Vector2i(w / 2 - 75, 3 * (h / 4) - 25), 150, 50, sf::Color::Cyan, L"Quitter", gameManager->getRenderWindow());
}

StatePauseMenu::~StatePauseMenu() {}

void StatePauseMenu::handleInput(double deltatime)
{
	sf::Event event;
	while (gameManager->getRenderWindow()->pollEvent(event))
	{
		if (playButton.isClicked())
		{
			StatePlayGame* playGame = dynamic_cast<StatePlayGame*>(this->gameManager->peekState(1));
			playGame->resume();
			this->gameManager->popState();
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
	sf::Font font = sf::Font();
	font.loadFromFile("CollegiateBlackFLF.ttf");

	pause = sf::Text("Pause", font, 35);
	pause.setFillColor(sf::Color::White);
	pause.setPosition(sf::Vector2f(w / 2 - 57, 1 * (h / 4) - 25));
	gameManager->getRenderWindow()->draw(pause);

	playButton.draw();
	quitButton.draw();
}
