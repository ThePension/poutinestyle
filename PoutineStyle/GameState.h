#pragma once
#include "GameManager.h"
class GameState
{
private:
	GameManager game;
public:
	GameState();
	~GameState();
	virtual void handleInput() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
};

