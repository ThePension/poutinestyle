#pragma once

#include "GameState.h"
#include "Button.h"
#include "Settings.h"

class StatePlayGame;

class StatePauseMenu : public GameState
{
	private:
		sf::View view;
		StatePlayGame* play;
		int w, h;
		Settings settings;
		bool bCommands = false, bSettings = false;

		Button playButton;
		Button backToMainMenu;
		Button quitButton;
		Button btnSettings;
		Button btnCommands;
		Button btnReturn;
		sf::Text pause;
		sf::Texture commandsTexture;
		sf::Sprite commandsSprite;

		Button btnSave;
		Button btnMetaDataON;
		Button btnMetaDataOFF;
		Button btnSensibilitySlow;
		Button btnSensibilityNormal;
		Button btnSensibility4k;
		Button btnVolume0;
		Button btnVolume25;
		Button btnVolume50;
		Button btnVolume75;
		Button btnVolume100;

	protected:
		void draw(double deltatime) override;
		void handleInput(double deltatime) override;
		void showSettingsLabel();
		void updateSelection();

	public:
		StatePauseMenu(GameManager* game, StatePlayGame* statePlayGame);
		~StatePauseMenu();

		void update(float deltaTime) override;
};

