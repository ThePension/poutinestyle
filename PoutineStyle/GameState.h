#pragma once
#include "GameManager.h"
#include "SFML/Graphics.hpp"
#include <SFML/Window.hpp>
#include <stdlib.h>
#include <math.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class GameState
{
protected:
	GameManager* gameManager;
	virtual void draw() = 0;
	virtual void handleInput() = 0;
public:
	GameState();
	~GameState();
	virtual void update() = 0;
};

