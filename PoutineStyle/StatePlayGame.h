#pragma once
#include "GameState.h"
#include "Player.h"
#include "Ennemy.h"
#include "Button.h"
#include "Entity.h"
#include "Chest.h"
#include <list>
#include <numbers>
#include <vector>
#include <math.h>

class StatePlayGame : public GameState
{
private:
	Player player;

	bool isPlayerMoving = false;
	sf::Keyboard::Key keysPressed;

	bool aPressed = false;
	bool dPressed = false;
	bool wPressed = false;
	bool sPressed = false;

	bool isMapDisplayed = false;

	int mapSize = 32;
	int movingSpeed = 100;
	int movingSpeedSPrint = 150;
	int blockWidth;
	int blockHeight;
	int textureSize = 64;

	int oldMouseX = 0, oldMouseY = 0;

	char** map;

	std::list<Ennemy*> ennemies; // Contains Ennemy Object
	std::list<Chest*> chests; // Contains Chest Object
	std::list<Entity*> entities; // Contains All Entities (Ennemy, Chest, ...)

	std::string mapFileFolder = "Map/"; // Needs to be changed and optimized. (ressource or relative path)
	std::string mapFileName = "Map_Example.txt";

	sf::Texture wallTextures, weaponTexture;
	sf::Sprite weaponSprite;
	double ZBuffer[1032];

protected:
	void draw(double dt) override;
	void handleInput() override;
	void parseMap2D();
	void drawMap2D();
	void drawMap3D(double dt);
	void updatePlayerPosition(sf::Vector2f newPos);
	sf::Vector2f rotateVectorMatrix(sf::Vector2f v, double angle);

public:
	StatePlayGame(GameManager * game);
	~StatePlayGame();
	void update(float deltaTime) override;
};

