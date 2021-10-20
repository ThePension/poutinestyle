#pragma once
#include <stack>
#include "GameState.h"
#include "StatePlayGame.h"
#include "StateMainMenu.h"
#include "StatePauseMenu.h"
#include <SFML/Graphics.hpp>

class GameManager
{
private:
	sf::RenderWindow window;
	std::stack<GameState*> states;
public:
	GameManager();
	void gameLoop();
	void pushState(GameState* state);
	void popState();
	void changeState(GameState* state);
	GameState* peekState();
};

