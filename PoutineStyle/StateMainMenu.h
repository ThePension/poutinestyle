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
	void draw(double deltatime) override;

public:
	StateMainMenu(GameManager * game);
	~StateMainMenu();
	void update(float deltaTime) override;
};

