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

	Button btnLevelAuto;
	Button btnLevel1;
	Button btnLevel2;
	Button btnLevel3;
	Button btnLevel4;
	Button btnLevel5;

	Button btnMetaDataON;
	Button btnMetaDataOFF;

	Button btnSensibilitySlow;
	Button btnSensibilityNormal;
	Button btnSensibility4k;

	Button btnDifficultyNoob;
	Button btnDifficultyPro;

	Button btnVolume0;
	Button btnVolume25;
	Button btnVolume50;
	Button btnVolume75;
	Button btnVolume100;

	bool settingsMode = false;
	Settings settings;

protected:
	void handleInput(double deltatime) override;
	void draw(double deltatime) override;
	void showSettingsLabel();
	void updateSelection();

public:
	StateMainMenu(GameManager * game);
	~StateMainMenu();
	void update(float deltaTime) override;
};

