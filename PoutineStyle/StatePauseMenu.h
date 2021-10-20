#pragma once
#include "SFML/Graphics.hpp"
#include "GameState.h"
class StatePauseMenu : public GameState
{
private:
	sf::View view;
	// Add buttons and more
public:
	StatePauseMenu();
	~StatePauseMenu();
	void handleInput() override;
	void update() override;
	void draw() override;
};

