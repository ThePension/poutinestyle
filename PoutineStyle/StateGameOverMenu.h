#pragma once
#include "GameState.h"
#include "StatePlayGame.h"
#include "Button.h"
class StateGameOverMenu : public GameState
{
private:
	Button replayButton;
	Button quitButton;
	sf::Text text, time;
	int player_score;
	sf::Time currentTime;

	bool win;

	int w, h;

protected:
	void handleInput(double deltatime) override;
	void draw(double deltatime) override;

public:
	StateGameOverMenu(GameManager* game, bool win, int player_score, sf::Clock timer);
	~StateGameOverMenu();
	void update(float deltaTime) override;
};

