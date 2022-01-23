#include "StateGameOverMenu.h"
StateGameOverMenu::StateGameOverMenu(GameManager* game, bool win, int player_score, sf::Clock timer)
{
	this->gameManager = game;
	this->win = win;
	this->player_score = player_score;
	currentTime = timer.getElapsedTime();

	w = gameManager->getWindowWidth();
	h = gameManager->getWindowHeight();

	float ratio = w / 500.f;

	replayButton = Button(sf::Vector2i(w / 2 - 75 * ratio, 2 * (h / 4) + 50), 150 * ratio, 50 * ratio, sf::Color::Red, L"Rejouer", gameManager->getRenderWindow());
	quitButton = Button(sf::Vector2i(w / 2 - 75 * ratio, 3 * (h / 4) + 0), 150 * ratio, 50 * ratio, sf::Color::Red, L"Quitter", gameManager->getRenderWindow());

	if (!win) {
		if (bgTexture.loadFromFile("Ressource/Picture/BackGround_GameOver.png"))
		{
			bgSprite.setTexture(bgTexture);
			bgSprite.setScale(0.5 * ratio, 0.5 * ratio);
		}
		else std::cout << "Failed to load GameOverMenu background image" << std::endl;
	}
	else {
		if (bgTexture.loadFromFile("Ressource/Picture/BackGround_Victory.png"))
		{
			bgSprite.setTexture(bgTexture);
			bgSprite.setScale(0.5 * ratio, 0.5 * ratio);
			
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
	text.setCharacterSize(60);
	float ratio = w / 500.f;

	// Display score
	std::string score = std::to_string(player_score);
	sf::Text lvlScore = sf::Text("SCORE : " + score, font, 40);
	lvlScore.setFillColor(sf::Color::White);
	lvlScore.setPosition(sf::Vector2f(0, 0));

	// Display time
	int currentTimeMinutes = int(currentTime.asSeconds() / 60);
	int currentTimeSeconds = int(currentTime.asSeconds() - currentTimeMinutes * 60);
	std::string timeMinute = std::to_string(currentTimeMinutes);
	std::string TimeSeconds = std::to_string(currentTimeSeconds);
	sf::Text lvlTime = sf::Text("TIME : " + timeMinute + "m" + TimeSeconds + "s", font, 40);
	lvlTime.setFillColor(sf::Color::White);
	lvlTime.setPosition(sf::Vector2f(0, 0));

	// Display both
	sf::Text lvlBoth = sf::Text("SCORE : " + score + "    TIME : " + timeMinute + "m" + TimeSeconds + "s", font, 40);
	lvlBoth.setFillColor(sf::Color::Black);
	lvlBoth.setPosition(sf::Vector2f(0, 0));

	if (win)
	{
		lvlScore.setPosition(sf::Vector2f(340 * ratio, 180 * ratio));
		lvlTime.setPosition(sf::Vector2f(340 * ratio, 205 * ratio));
		gameManager->getRenderWindow()->draw(lvlScore);
		gameManager->getRenderWindow()->draw(lvlTime);
	}
	else
	{
		lvlBoth.setPosition(sf::Vector2f(15 * ratio, 60 * ratio));
		gameManager->getRenderWindow()->draw(lvlBoth);
	}

	replayButton.draw();
	quitButton.draw();
}
