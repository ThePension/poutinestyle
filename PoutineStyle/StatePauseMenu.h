#pragma once
#include "GameState.h"
class StatePauseMenu : public GameState
{
private:
	sf::View view;
	// Add buttons and more
protected:
	void draw() override;
	void handleInput() override;
public:
	StatePauseMenu();
	~StatePauseMenu();
	void update(float deltaTime) override;
};

