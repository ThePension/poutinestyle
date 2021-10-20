#pragma once
#include "GameState.h"
#include "SFML/Graphics.hpp"
class StateMainMenu  : public GameState
{
private:
	sf::View view;
	// Add buttons and more

public:
	StateMainMenu();
	~StateMainMenu();
	void handleInput() override;
	void update() override;
	void draw() override;
};

