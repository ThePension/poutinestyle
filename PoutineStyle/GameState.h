#pragma once
// #include "GameManager.h"
#include "SFML/Graphics.hpp"
class GameState
{
private:
	// GameManager game;
public:
	GameState();
	~GameState();
	virtual void handleInput() abstract;
	virtual void update() abstract;
	virtual void draw() abstract;
};

