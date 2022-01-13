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
	virtual void draw(double deltatime) = 0;
	virtual void handleInput(double deltatime) = 0;
	sf::Texture bgTexture;
	sf::Sprite bgSprite;

public:
	GameState();
	~GameState();
	virtual void update(float deltatime) = 0;
};

