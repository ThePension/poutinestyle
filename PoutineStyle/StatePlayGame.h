#pragma once
#include "GameState.h"
#include "Player.h"
#include "Ennemy.h"
#include "Button.h"
#include "Entity.h"
#include "Chest.h"
#include "Bullet.h"
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
	bool isShooting = false;

	bool isMapDisplayed = false;
	bool isGamePaused = false;

	int mapSize = 32;
	int movingSpeed = 3;
	int movingSpeedSPrint = 150;
	int blockWidth;
	int blockHeight;
	int textureSize = 64;
	int yOffset = 50;
	float speedFactor = 5;

	int oldMouseX = 0, oldMouseY = 0;

	char** map;
	Entity* entityMap[32][32]; // A map with entity Objects
	std::list<Entity*> entitiesToDraw; // Contains Entity Objects that must be drawn

	std::list<Ennemy*> ennemies; // Contains Ennemy Objects
	std::list<Chest*> chests; // Contains Chest Objects
	std::list<Bullet*> bullets;

	std::string mapFileFolder = "Map/"; // Needs to be changed and optimized. (ressource or relative path)
	std::string mapFileName = "Map_Example3.txt";

	sf::Texture wallTextures, weaponTexture, imgAimCursor;
	sf::Sprite weaponSprite;
	double ZBuffer[1032]; // Contains perpendicular distance from player to closest wall (usefull for rendering Entity object)

	Entity* InteractedEntity = nullptr;

	void draw(double dt) override;
	void handleInput(double deltatime) override;
	void parseMap2D();
	void drawMap2D();
	void drawMap3D(double dt);
	void displayPauseMenu();
	void showCursor();
	void RenderingFloor(double dt);
	void updatePlayerPosition(sf::Vector2f newPos);
	void hud();
	sf::Vector2f rotateVectorMatrix(sf::Vector2f v, double angle);
	Entity* getInteractedEntity();

public:
	StatePlayGame(GameManager * game);
	~StatePlayGame();
	void update(float deltaTime) override;
};