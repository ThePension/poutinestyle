#include "StateMainMenu.h"
StateMainMenu::StateMainMenu(GameManager * game) {

	// Music
	sf::Music mainMenuMusic;
	mainMenuMusic.openFromFile("Ressource/Music/MainMenuMusic.wav");
	mainMenuMusic.play();

	this->gameManager = game;

	// Create buttons
	int w = gameManager->getWindowWidth();
	int h = gameManager->getWindowHeight();

	playButton = Button(sf::Vector2i(w / 2 - 75, 1*(h / 4) - 25), 150, 50, sf::Color::Black, L"Jouer", gameManager->getRenderWindow());
	settingsButton = Button(sf::Vector2i(w / 2 - 75, 2 * (h / 4) - 25), 150, 50, sf::Color::Black, L"Parametres", gameManager->getRenderWindow());
	quitButton = Button(sf::Vector2i(w / 2 - 75, 3 * (h / 4) - 25), 150, 50, sf::Color::Black, L"Quitter", gameManager->getRenderWindow());

	this->btnLevelAuto = Button(sf::Vector2i(w / 2 - 160, 1 * (h / 7) - 25), 70, 50, sf::Color::Black, L"auto", gameManager->getRenderWindow());
	this->btnLevel1 = Button(sf::Vector2i(w / 2 - 160 + 90, 1 * (h / 7) - 25), 40, 50, sf::Color::Black, L"1", gameManager->getRenderWindow());
	this->btnLevel2 = Button(sf::Vector2i(w / 2 - 160 + 90 + 60, 1 * (h / 7) - 25), 40, 50, sf::Color::Black, L"2", gameManager->getRenderWindow());
	this->btnLevel3 = Button(sf::Vector2i(w / 2 - 160 + 90 + 2*60, 1 * (h / 7) - 25), 40, 50, sf::Color::Black, L"3", gameManager->getRenderWindow());
	this->btnLevel4 = Button(sf::Vector2i(w / 2 - 160 + 90 + 3*60, 1 * (h / 7) - 25), 40, 50, sf::Color::Black, L"4", gameManager->getRenderWindow());
	this->btnLevel5 = Button(sf::Vector2i(w / 2 - 160 + 90 + 4*60, 1 * (h / 7) - 25), 40, 50, sf::Color::Black, L"5", gameManager->getRenderWindow());

	this->btnMetaDataON = Button(sf::Vector2i(w / 2 - 25, 2 * (h / 7) - 25), 60, 50, sf::Color::Black, L"ON", gameManager->getRenderWindow());
	this->btnMetaDataOFF = Button(sf::Vector2i(w / 2 - 25 + 80, 2 * (h / 7) - 25), 60, 50, sf::Color::Black, L"OFF", gameManager->getRenderWindow());

	this->btnSensibilitySlow = Button(sf::Vector2i(w / 2 - 120, 3 * (h / 7) - 25), 80, 50, sf::Color::Black, L"Lent", gameManager->getRenderWindow());
	this->btnSensibilityNormal = Button(sf::Vector2i(w / 2 - 120 + 100, 3 * (h / 7) - 25), 90, 50, sf::Color::Black, L"Normal", gameManager->getRenderWindow());
	this->btnSensibility4k = Button(sf::Vector2i(w / 2 - 120 + 100 + 110, 3 * (h / 7) - 25), 120, 50, sf::Color::Black, L"Special 4k", gameManager->getRenderWindow());

	this->btnDifficultyNoob = Button(sf::Vector2i(w / 2 - 120, 4 * (h / 7) - 25), 155, 50, sf::Color::Black, L"Sans talent", gameManager->getRenderWindow());
	this->btnDifficultyPro = Button(sf::Vector2i(w / 2 - 120 + 175, 4 * (h / 7) - 25), 155, 50, sf::Color::Black, L"Fais moi mal", gameManager->getRenderWindow());

	this->btnVolume0 = Button(sf::Vector2i(w / 2 - 120, 5 * (h / 7) - 25), 50, 50, sf::Color::Black, L"0", gameManager->getRenderWindow());
	this->btnVolume25 = Button(sf::Vector2i(w / 2 - 120 + 70, 5 * (h / 7) - 25), 50, 50, sf::Color::Black, L"25", gameManager->getRenderWindow());
	this->btnVolume50 = Button(sf::Vector2i(w / 2 - 120 + 2*70, 5 * (h / 7) - 25), 50, 50, sf::Color::Black, L"50", gameManager->getRenderWindow());
	this->btnVolume75 = Button(sf::Vector2i(w / 2 - 120 + 3*70, 5 * (h / 7) - 25), 50, 50, sf::Color::Black, L"75", gameManager->getRenderWindow());
	this->btnVolume100 = Button(sf::Vector2i(w / 2 - 120 + 4*70, 5 * (h / 7) - 25), 50, 50, sf::Color::Black, L"100", gameManager->getRenderWindow());

	if (bgTexture.loadFromFile("Ressource/Picture/BackGround_MainMenu.png"))
	{
		bgSprite.setTexture(bgTexture);
		bgSprite.setScale(0.5, 0.5);
	}
	else std::cout << "Failed to load GameOverMenu failed background image" << std::endl;
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
				this->quitButton = Button(sf::Vector2i(gameManager->getWindowWidth() / 2 - 75, 3 * (gameManager->getWindowHeight() / 4) - 25), 150, 50, sf::Color::Black, L"Quitter", gameManager->getRenderWindow());
				this->settingsMode = false;
			}
			else if (btnLevelAuto.isClicked())
			{
				settings.setLevel(0);
			}
			else if (btnLevel1.isClicked())
			{
				settings.setLevel(1);
			}
			else if (btnLevel2.isClicked())
			{
				settings.setLevel(2);
			}
			else if (btnLevel3.isClicked())
			{
				settings.setLevel(3);
			}
			else if (btnLevel4.isClicked())
			{
				settings.setLevel(4);
			}
			else if (btnLevel5.isClicked())
			{
				settings.setLevel(5);
			}
			else if (btnMetaDataON.isClicked())
			{
				settings.setShowMetaData(true);
				this->gameManager->setDrawFPS(true);
			}
			else if (btnMetaDataOFF.isClicked())
			{
				settings.setShowMetaData(false);
				this->gameManager->setDrawFPS(false);
			}
			else if (btnSensibilitySlow.isClicked())
			{
				settings.setSensibility(3);
			}
			else if (btnSensibilityNormal.isClicked())
			{
				settings.setSensibility(5);
			}
			else if (btnSensibility4k.isClicked())
			{
				settings.setSensibility(10);
			}
			else if (btnDifficultyNoob.isClicked())
			{
				settings.setDifficulty(1);
			}
			else if (btnDifficultyPro.isClicked())
			{
				settings.setDifficulty(2);
			}
			else if (btnVolume0.isClicked())
			{
				settings.setVolume(0);
			}
			else if (btnVolume25.isClicked())
			{
				settings.setVolume(25);
			}
			else if (btnVolume50.isClicked())
			{
				settings.setVolume(50);
			}
			else if (btnVolume75.isClicked())
			{
				settings.setVolume(75);
			}
			else if (btnVolume100.isClicked())
			{
				settings.setVolume(100);
			}

			this->gameManager->gameMusic->setVolume(settings.getVolume());
			this->gameManager->menuMusic->setVolume(settings.getVolume());
			updateSelection();
		}
		else
		{
			if (playButton.isClicked()) {
				StatePlayGame* statePlayGame = new StatePlayGame(this->gameManager, settings);
				this->gameManager->changeState(statePlayGame);
				return;
			}
			else if (settingsButton.isClicked()) {
				this->settingsMode = true;
				this->quitButton = Button(sf::Vector2i(gameManager->getWindowWidth() / 2 - 75, 6 * (gameManager->getWindowHeight() / 7)), 150, 50, sf::Color::Black, L"Enregistrer", gameManager->getRenderWindow());
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
	// Draw background image
	gameManager->getRenderWindow()->draw(bgSprite);

	if (this->settingsMode)
	{
		btnLevelAuto.draw();
		btnLevel1.draw();
		btnLevel2.draw();
		btnLevel3.draw();
		btnLevel4.draw();
		btnLevel5.draw();
		btnMetaDataON.draw();
		btnSensibilitySlow.draw();
		btnSensibilityNormal.draw();
		btnSensibility4k.draw();
		btnDifficultyNoob.draw();
		btnDifficultyPro.draw();
		btnVolume0.draw();
		btnVolume25.draw();
		btnVolume50.draw();
		btnVolume75.draw();
		btnVolume100.draw();
		btnMetaDataOFF.draw();

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
	int wAlign = gameManager->getWindowWidth() / 2 - 230;
	int hAlign = gameManager->getWindowHeight() / 7;

	sf::Font font = gameManager->getFont();

	sf::Text lblLevel = sf::Text("Map :", font, 15);
	lblLevel.setFillColor(sf::Color::White);
	lblLevel.setPosition(sf::Vector2f(wAlign, 1.f * hAlign - 7.f));
	gameManager->getRenderWindow()->draw(lblLevel);

	sf::Text lblMetaData = sf::Text("Afficher Meta Data : ", font, 15);
	lblMetaData.setFillColor(sf::Color::White);
	lblMetaData.setPosition(sf::Vector2f(wAlign, 2.f * hAlign - 7.f));
	gameManager->getRenderWindow()->draw(lblMetaData);

	sf::Text lblSensi = sf::Text("Sensibilite :", font, 15);
	lblSensi.setFillColor(sf::Color::White);
	lblSensi.setPosition(sf::Vector2f(wAlign, 3.f * hAlign - 7.f));
	gameManager->getRenderWindow()->draw(lblSensi);

	sf::Text lblDiff = sf::Text("Difficulte :", font, 15);
	lblDiff.setFillColor(sf::Color::White);
	lblDiff.setPosition(sf::Vector2f(wAlign, 4.f * hAlign - 7.f));
	gameManager->getRenderWindow()->draw(lblDiff);

	sf::Text lblVolume = sf::Text("Volume : ", font, 15);
	lblVolume.setFillColor(sf::Color::White);
	lblVolume.setPosition(sf::Vector2f(wAlign, 5.f * hAlign - 7.f));
	gameManager->getRenderWindow()->draw(lblVolume);
}

void StateMainMenu::updateSelection()
{
	btnLevelAuto.selected(false);
	btnLevel1.selected(false);
	btnLevel2.selected(false);
	btnLevel3.selected(false);
	btnLevel4.selected(false);
	btnLevel5.selected(false);
	btnMetaDataON.selected(false);
	btnSensibilitySlow.selected(false);
	btnSensibilityNormal.selected(false);
	btnSensibility4k.selected(false);
	btnDifficultyNoob.selected(false);
	btnDifficultyPro.selected(false);
	btnVolume0.selected(false);
	btnVolume25.selected(false);
	btnVolume50.selected(false);
	btnVolume75.selected(false);
	btnVolume100.selected(false);
	btnMetaDataOFF.selected(false);

	switch (settings.getDifficulty())
	{
	case 1:
		btnDifficultyNoob.selected(true);
		break;
	case 2:
		btnDifficultyPro.selected(true);
		break;
	}

	switch (settings.getLevel())
	{
	case 0:
		btnLevelAuto.selected(true);
		break;
	case 1:
		btnLevel1.selected(true);
		break;
	case 2:
		btnLevel2.selected(true);
		break;
	case 3:
		btnLevel3.selected(true);
		break;
	case 4:
		btnLevel4.selected(true);
		break;
	case 5:
		btnLevel5.selected(true);
		break;
	}

	switch (settings.getSensibility())
	{
	case 3:
		btnSensibilitySlow.selected(true);
		break;
	case 5:
		btnSensibilityNormal.selected(true);
		break;
	case 10:
		btnSensibility4k.selected(true);
		break;
	}

	switch (settings.getVolume())
	{
	case 0:
		btnVolume0.selected(true);
		break;
	case 25:
		btnVolume25.selected(true);
		break;
	case 50:
		btnVolume50.selected(true);
		break;
	case 75:
		btnVolume75.selected(true);
		break;
	case 100:
		btnVolume100.selected(true);
		break;
	}

	if (settings.getShowMetaData())
	{
		btnMetaDataON.selected(true);
	}
	else
	{
		btnMetaDataOFF.selected(true);
	}
}


