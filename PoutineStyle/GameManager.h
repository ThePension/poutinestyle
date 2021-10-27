#pragma once
#include <stack>
#include <SFML/Graphics.hpp>

// Needed to avoid circular dependency 
// https://stackoverflow.com/questions/625799/resolve-build-errors-due-to-circular-dependency-amongst-classes
class GameState;

class GameManager
{
private:
	
	std::stack<GameState*> states;
	int windowWidth = 1032;
	int windowHeight = 1032;
	sf::RenderWindow* window;
public:
	int getWindowWidth() { return this->windowWidth; }
	int getWindowHeight() { return this->windowHeight; }
	sf::RenderWindow* getRenderWindow() { return this->window; }
	
	GameManager();
	void gameLoop();
	void pushState(GameState* state);
	void popState();
	void changeState(GameState* state);
	bool containsState(GameState* state);
	GameState* peekState();
};

