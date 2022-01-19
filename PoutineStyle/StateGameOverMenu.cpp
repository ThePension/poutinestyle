#include "StateGameOverMenu.h"
StateGameOverMenu::StateGameOverMenu(GameManager* game, bool win, int player_score)
{
	this->gameManager = game;
	this->win = win;
	this->player_score = player_score;

	w = gameManager->getWindowWidth();
	h = gameManager->getWindowHeight();

	replayButton = Button(sf::Vector2i(w / 2 - 75, 2 * (h / 4) + 50), 150, 50, sf::Color::Red, L"Rejouer", gameManager->getRenderWindow());
	quitButton = Button(sf::Vector2i(w / 2 - 75, 3 * (h / 4) + 0), 150, 50, sf::Color::Red, L"Quitter", gameManager->getRenderWindow());

	if (!win) {
		if (bgTexture.loadFromFile("Ressource/Picture/BackGround_GameOver.png"))
		{
			bgSprite.setTexture(bgTexture);
			bgSprite.setScale(0.5, 0.5);
		}
		else std::cout << "Failed to load GameOverMenu background image" << std::endl;
	}
	else {
		if (bgTexture.loadFromFile("Ressource/Picture/BackGround_Victory.png"))
		{
			bgSprite.setTexture(bgTexture);
			bgSprite.setScale(0.5, 0.5);
			
		}
		else std::cout << "Failed to load victory background image" << std::endl;
	}
}
StateGameOverMenu::~StateGameOverMenu() {

}
void StateGameOverMenu::handleInput(double deltatime) {
	sf::Event event;
	while (gameManager->getRenderWindow()->pollEvent(event))
	{
		if (replayButton.isClicked())
		{
			/*
			StatePlayGame* statePlayGame = new StatePlayGame(this->gameManager); // Create new PlayGame state
			//StatePlayGame* statePlayGame = new StatePlayGame(this->gameManager, "Lvl1.txt", 16);
			gameManager->changeState(statePlayGame); // Change current state for new PlayGame state
			*/
			StateMainMenu* stateMainMenu = new StateMainMenu(this->gameManager);
			gameManager->changeState(stateMainMenu);
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
	// Draw background image
	gameManager->getRenderWindow()->draw(bgSprite);

	sf::Font font = gameManager->getFont();
	text.setFont(font);
	text.setCharacterSize(30);

	// Display score
	std::string score = std::to_string(player_score);
	sf::Text lblScore = sf::Text("Score : " + score, font);
	lblScore.setFillColor(sf::Color::White);
	lblScore.setPosition(sf::Vector2f(0, 0));

	if (win)
	{
		lblScore.setPosition(sf::Vector2f(300, 200));
	}
	else
	{
		lblScore.setPosition(sf::Vector2f(20, 20));
	}

	gameManager->getRenderWindow()->draw(lblScore);
	replayButton.draw();
	quitButton.draw();
}
