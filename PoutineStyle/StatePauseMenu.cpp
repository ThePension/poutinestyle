#include "StatePauseMenu.h"
#include "StatePlayGame.h"

StatePauseMenu::StatePauseMenu(GameManager* game, StatePlayGame *statePlayGame)
{
	this->gameManager = game;

	this->play = statePlayGame;
	this->settings = this->play->getSettings();

	w = gameManager->getWindowWidth();
	h = gameManager->getWindowHeight();

	int ratio = w / 500;

	// Buttons for pause
	playButton = Button(sf::Vector2i(int(w / 2 - 75* ratio), int(1.5 * (h / 4) - 25)), 150 * ratio, 50 * ratio, sf::Color::Black, L"Reprendre", gameManager->getRenderWindow());
	btnCommands = Button(sf::Vector2i(int(w / 2 - 75 * ratio), int(2 * (h / 4) - 25)), 150 * ratio, 50 * ratio, sf::Color::Black, L"Commandes", gameManager->getRenderWindow());
	backToMainMenu = Button(sf::Vector2i(int(w / 2 - 75 * ratio), int(2.5 * (h / 4) - 25)), 150 * ratio, 50 * ratio, sf::Color::Black, L"Menu principal", gameManager->getRenderWindow());
	btnSettings = Button(sf::Vector2i(int(w / 2 - 75 * ratio), int(3 * (h / 4) - 25)), 150 * ratio, 50 * ratio, sf::Color::Black, L"Parametres", gameManager->getRenderWindow());
	quitButton = Button(sf::Vector2i(int(w / 2 - 75 * ratio), int(3.5 * (h / 4) - 25)), 150 * ratio, 50 * ratio, sf::Color::Black, L"Quitter", gameManager->getRenderWindow());

	// Buttons for commands
	btnReturn = Button(sf::Vector2i(int(w / 2 - 75 * ratio), int(3.5 * (h / 4) - 25)), 150 * ratio, 50 * ratio, sf::Color::Black, L"Retour", gameManager->getRenderWindow());

	// Buttons for settings
	this->btnSave = Button(sf::Vector2i(w / 2 - 75 * ratio, 6 * (h / 7)), 150* ratio, 50 * ratio, sf::Color::Black, L"Enregistrer", gameManager->getRenderWindow());

	this->btnMetaDataON = Button(sf::Vector2i(w / 2 - 25 * ratio, 2 * (h / 7) - 25), 60 * ratio, 50 * ratio, sf::Color::Black, L"ON", gameManager->getRenderWindow());
	this->btnMetaDataOFF = Button(sf::Vector2i(w / 2 - 25 * ratio + 80 * ratio, 2 * (h / 7) - 25), 60 * ratio, 50 * ratio, sf::Color::Black, L"OFF", gameManager->getRenderWindow());

	this->btnSensibilitySlow = Button(sf::Vector2i(w / 2 - 120 * ratio, 3 * (h / 7) - 25), 80 * ratio, 50 * ratio, sf::Color::Black, L"Lent", gameManager->getRenderWindow());
	this->btnSensibilityNormal = Button(sf::Vector2i(w / 2 - 120 * ratio + 100 * ratio, 3 * (h / 7) - 25), 90 * ratio, 50 * ratio, sf::Color::Black, L"Normal", gameManager->getRenderWindow());
	this->btnSensibility4k = Button(sf::Vector2i(w / 2 - 120 * ratio + 100 * ratio + 110 * ratio, 3 * (h / 7) - 25), 120 * ratio, 50 * ratio, sf::Color::Black, L"Special 4k", gameManager->getRenderWindow());

	this->btnVolume0 = Button(sf::Vector2i(w / 2 - 120 * ratio, 4 * (h / 7) - 25), 50 * ratio, 50 * ratio, sf::Color::Black, L"0", gameManager->getRenderWindow());
	this->btnVolume25 = Button(sf::Vector2i(w / 2 - 120 * ratio + 70 * ratio, 4 * (h / 7) - 25), 50 * ratio, 50 * ratio, sf::Color::Black, L"25", gameManager->getRenderWindow());
	this->btnVolume50 = Button(sf::Vector2i(w / 2 - 120 * ratio + 2 * 70 * ratio, 4 * (h / 7) - 25), 50 * ratio, 50 * ratio, sf::Color::Black, L"50", gameManager->getRenderWindow());
	this->btnVolume75 = Button(sf::Vector2i(w / 2 - 120 * ratio + 3 * 70 * ratio, 4 * (h / 7) - 25), 50 * ratio, 50 * ratio, sf::Color::Black, L"75", gameManager->getRenderWindow());
	this->btnVolume100 = Button(sf::Vector2i(w / 2 - 120 * ratio + 4 * 70 * ratio, 4 * (h / 7) - 25), 50 * ratio, 50 * ratio, sf::Color::Black, L"100", gameManager->getRenderWindow());

	if (bgTexture.loadFromFile("Ressource/Picture/BackGround_MainMenu.png"))
	{
		bgSprite.setTexture(bgTexture);
		bgSprite.setScale(0.5 * ratio, 0.5 * ratio);
	}
	else std::cout << "Failed to load MainMenu background image" << std::endl;

	if (commandsTexture.loadFromFile("Ressource/Picture/BackGround_UserGuide.png"))
	{
		commandsSprite.setTexture(commandsTexture);
		commandsSprite.setScale(0.5 * ratio, 0.5 * ratio);
	}
	else std::cout << "Failed to load user guide background image" << std::endl;
}

StatePauseMenu::~StatePauseMenu() {}

void StatePauseMenu::handleInput(double deltatime)
{
	sf::Event event;
	while (gameManager->getRenderWindow()->pollEvent(event))
	{
		if (!bCommands)
		{
			if (!bSettings)
			{
				if (!bWaitCommand)
				{
					if (!bWaitSettings)
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
						else if (btnSettings.isClicked())
						{
							bSettings = true;
						}
						else if (btnCommands.isClicked())
						{
							bCommands = true;
						}
					}
					else
					{
						if (btnSave.isReleased())
						{
							bWaitSettings = false;
						}
					}
				}
				else
				{
					if (btnReturn.isReleased())
					{
						bWaitCommand = false;
					}
				}
			}
			else
			{
				if (btnMetaDataON.isClicked())
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
				else if (btnSave.isClicked())
				{
					bSettings = false;
					bWaitSettings = true;
				}

				this->play->setSettings(this->settings);
				updateSelection();
			}
		}
		else
		{
			if (btnReturn.isClicked())
			{
				bCommands = false;
				bWaitCommand = true;
			}
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
	if (!bCommands)
	{
		// Draw background image
		gameManager->getRenderWindow()->draw(bgSprite);

		if (!bSettings)
		{
			sf::Font font = gameManager->getFont();

			pause = sf::Text("Pause", font, 70);
			pause.setFillColor(sf::Color::White);
			pause.setPosition(sf::Vector2f(w / 2 - 110.f, 1 * (h / 4) - 50.f));
			gameManager->getRenderWindow()->draw(pause);

			playButton.draw();
			quitButton.draw();
			backToMainMenu.draw();
			btnSettings.draw();
			btnCommands.draw();
		}
		else // display settings
		{
			btnSave.draw();
			btnMetaDataON.draw();
			btnSensibilitySlow.draw();
			btnSensibilityNormal.draw();
			btnSensibility4k.draw();
			btnVolume0.draw();
			btnVolume25.draw();
			btnVolume50.draw();
			btnVolume75.draw();
			btnVolume100.draw();
			btnMetaDataOFF.draw();

			showSettingsLabel();
		}		
	}
	else // display commands
	{
		gameManager->getRenderWindow()->draw(commandsSprite);
		btnReturn.draw();
	}
}

void StatePauseMenu::showSettingsLabel()
{
	float ratio = gameManager->getWindowWidth() / 500.f;
	int wAlign = gameManager->getWindowWidth() / 2 - 230 * ratio;
	int hAlign = gameManager->getWindowHeight() / 7;

	float fontSize = 15.f * ratio;
	sf::Font font = gameManager->getFont();
	sf::Text lblMetaData = sf::Text("Afficher Meta Data : ", font, fontSize);
	lblMetaData.setFillColor(sf::Color::White);
	lblMetaData.setPosition(sf::Vector2f(wAlign, 2.f * hAlign));
	gameManager->getRenderWindow()->draw(lblMetaData);

	sf::Text lblSensi = sf::Text("Sensibilite :", font, fontSize);
	lblSensi.setFillColor(sf::Color::White);
	lblSensi.setPosition(sf::Vector2f(wAlign, 3.f * hAlign));
	gameManager->getRenderWindow()->draw(lblSensi);

	sf::Text lblVolume = sf::Text("Volume : ", font, fontSize);
	lblVolume.setFillColor(sf::Color::White);
	lblVolume.setPosition(sf::Vector2f(wAlign, 4.f * hAlign));
	gameManager->getRenderWindow()->draw(lblVolume);
}

void StatePauseMenu::updateSelection()
{
	btnMetaDataON.selected(false);
	btnSensibilitySlow.selected(false);
	btnSensibilityNormal.selected(false);
	btnSensibility4k.selected(false);
	btnVolume0.selected(false);
	btnVolume25.selected(false);
	btnVolume50.selected(false);
	btnVolume75.selected(false);
	btnVolume100.selected(false);
	btnMetaDataOFF.selected(false);


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