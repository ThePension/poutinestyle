#pragma once
#include "GameState.h"
#include "StatePlayGame.h"
#include "Button.h"
class StateGameOverMenu : public GameState
{
private:
	Button replayButton;
	Button quitButton;
	bool isReplayClicked = false;

protected:
	void handleInput() override;
	void draw() override;

public:
	StateGameOverMenu(GameManager* game);
	~StateGameOverMenu();
	void update() override;
};

