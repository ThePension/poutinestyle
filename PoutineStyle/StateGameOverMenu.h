#pragma once
#include "GameState.h"
#include "StatePlayGame.h"
#include "Button.h"
class StateGameOverMenu : public GameState
{
private:
	Button replayButton;
	Button quitButton;
	sf::Text text;
	sf::Texture bgTexture;
	sf::Sprite bgSprite;

	bool win;

	int w, h;

protected:
	void handleInput(double deltatime) override;
	void draw(double deltatime) override;

public:
	StateGameOverMenu(GameManager* game, bool win);
	~StateGameOverMenu();
	void update(float deltaTime) override;
};

