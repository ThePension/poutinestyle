#pragma once

#include "GameState.h"
#include "StatePlayGame.h"
#include "Button.h"
#include "Settings.h"

class StateMainMenu  : public GameState
{
private:
	Button playButton;
	Button quitButton;
	Button settingsButton;

	Button btnLevel;
	Button btnMetaData;
	Button btnSensibility;
	Button btnDifficulty;
	Button btnVolume;

	bool settingsMode = false;
	Settings settings;

protected:
	void handleInput(double deltatime) override;
	void draw(double deltatime) override;
	void showSettingsLabel();

public:
	StateMainMenu(GameManager * game);
	~StateMainMenu();
	void update(float deltaTime) override;
};

