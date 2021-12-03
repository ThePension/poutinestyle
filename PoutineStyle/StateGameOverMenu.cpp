#include "StateGameOverMenu.h"
StateGameOverMenu::StateGameOverMenu(GameManager* game, bool win) {
	this->gameManager = game;
	this->win = win;

	w = gameManager->getWindowWidth();
	h = gameManager->getWindowHeight();

	replayButton = Button(sf::Vector2i(w / 2 - 75, 2 * (h / 4) - 25), 150, 50, sf::Color::Cyan, L"Rejouer", gameManager->getRenderWindow());
	quitButton = Button(sf::Vector2i(w / 2 - 75, 3 * (h / 4) - 25), 150, 50, sf::Color::Cyan, L"Quitter", gameManager->getRenderWindow());
}
StateGameOverMenu::~StateGameOverMenu() {

}
void StateGameOverMenu::handleInput(double deltatime) {
	sf::Event event;
	while (gameManager->getRenderWindow()->pollEvent(event))
	{
		if (replayButton.isClicked())
		{
			StatePlayGame* statePlayGame = new StatePlayGame(this->gameManager); // Create new PlayGame state
			//StatePlayGame* statePlayGame = new StatePlayGame(this->gameManager, "Lvl1.txt", 16);
			gameManager->changeState(statePlayGame); // Change current state for new PlayGame state
			return;
		}
		else if (quitButton.isClicked())
		{
			// Quit application
			exit(0);
		}
	}
}
void StateGameOverMenu::update(float deltaTime)
{
	draw(deltaTime);
	handleInput(deltaTime);
}

void StateGameOverMenu::draw(double deltatime)
{
	sf::Font font = sf::Font();
	font.loadFromFile("CollegiateBlackFLF.ttf");

	text.setFont(font);
	text.setCharacterSize(34);
	if (win)
	{
		text.setString("VICTOIRE !!!");
	}
	else
	{
		text.setString("DEFAITE ...");
	}
	
	text.setFillColor(sf::Color::White);
	text.setPosition(sf::Vector2f(w / 2 - 57, 1 * (h / 4) - 25));
	gameManager->getRenderWindow()->draw(text);

	replayButton.draw();
	quitButton.draw();
}
