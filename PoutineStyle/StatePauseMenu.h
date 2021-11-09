#pragma once
#include "GameState.h"
class StatePauseMenu : public GameState
{
private:
	sf::View view;
	// Add buttons and more
protected:
	void draw(double deltatime) override;
	void handleInput(double deltatime) override;
public:
	StatePauseMenu();
	~StatePauseMenu();
	void update(float deltaTime) override;
};

