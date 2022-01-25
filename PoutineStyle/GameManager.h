#pragma once
#include <stack>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Needed to avoid circular dependency 
// https://stackoverflow.com/questions/625799/resolve-build-errors-due-to-circular-dependency-amongst-classes
class GameState;

class GameManager
{
private:
	std::stack<GameState*> states;
	int windowWidth = 1000;
	int windowHeight = 1000;
	sf::RenderWindow* window;
	sf::Clock clock;
	float deltaTime;
	sf::Font font;
	bool drawFPS = false;
public:
	int getWindowWidth() { return this->windowWidth; }
	int getWindowHeight() { return this->windowHeight; }
	sf::RenderWindow* getRenderWindow() { return this->window; }
	
	GameManager();
	~GameManager();
	void gameLoop();
	void pushState(GameState* state);
	void popState();
	void changeState(GameState* state);
	void popBeforeLastState();
	GameState* peekState(int i=0);
	sf::Font getFont() { return this->font;  }
	void setDrawFPS(bool drawFPS) { this->drawFPS = drawFPS; }

	// Music 
	sf::Music* gameMusic = nullptr;
	sf::Music* menuMusic = nullptr;
	bool isfirstMusic = true;


};

