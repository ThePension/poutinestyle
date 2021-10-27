#pragma once
#include "GameState.h"
#include "StatePlayGame.h"
#include "Button.h"
class StateMainMenu  : public GameState
{
private:
	Button playButton;
	Button quitButton;
	Button settingsButton;

protected:
	void handleInput() override;
	void draw() override;

public:
	StateMainMenu(GameManager * game);
	~StateMainMenu();
	void update() override;
};

