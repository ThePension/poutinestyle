#pragma once
#include "GameState.h"
class StateMainMenu  : public GameState
{
private:
	sf::View view;
	// Add buttons and more

protected:
	void handleInput() override;
	void draw() override;

public:
	StateMainMenu();
	~StateMainMenu();
	void update() override;
};

