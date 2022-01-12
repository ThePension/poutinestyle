#pragma once
#include "GameState.h"
#include "Player.h"
#include "Ennemy.h"
#include "Button.h"
#include "Entity.h"
#include "Chest.h"
#include "Ammo.h"
#include "Medikit.h"
#include "Bullet.h"
#include <list>
#include <numbers>
#include <vector>
#include <math.h>
#include "StatePauseMenu.h"
#include "StateGameOverMenu.h"
#include "Key.h"
#include "StateMainMenu.h"
#include "Shotgun.h"
#include "Guard.h"
#include "Wall.h"
#include "General.h"
#include "Uzi.h"
#include "Door.h"
#include "GrenadeLauncher.h"
#include "Settings.h"

class StatePlayGame : public GameState
{
private:
	Player * player;

	bool isPlayerMoving = false;
	sf::Keyboard::Key keysPressed;

	bool qPressed = false;//burst firing

	bool aPressed = false;
	bool dPressed = false;
	bool wPressed = false;
	bool sPressed = false;
	bool isShooting = false;

	bool isMapDisplayed = false;
	bool isGamePaused = false;
	bool isFinished = false;
	bool hard = false;

	int mapSize;
	int movingSpeed = 3;
	int movingSpeedSPrint = 150;
	float blockWidth;
	float blockHeight;
	int textureSize = 256;
	int yOffset = 50;
	float speedFactor = 5;
	bool isBursting = false; 

	Settings settings;

	int oldMouseX = 0, oldMouseY = 0;

	char** map;
	Entity* entityMap[64][64]; // A map with entity Objects
	std::list<Entity*> entities; // Contains every entities

	sf::VertexArray* linesFloor = nullptr;
	sf::VertexArray* lines = nullptr;
	sf::VertexArray* linesOverride = nullptr;

	std::string mapFilePath;
	std::map<std::string, int> levels;
	std::map<std::string, int>::iterator actualLevel;

	sf::Texture wallTextures, imgAimCursor;
	sf::Sprite weaponSprite;
	double ZBuffer[1032]; // Contains perpendicular distance from player to closest wall (usefull for rendering Entity object)

	Entity* InteractedEntity = nullptr;

	// HUD static stuff
	sf::RectangleShape * hudUp, * hudDownL, * hudDownML, * hudDownM, * hudDownMR, * hudDownR;


	void draw(double dt) override;
	void handleInput(double deltatime) override;
	void parseMap2D();
	void drawMap2D();
	void drawMiniMap();
	void renderingWalls(double dt);
	void castRay(int x, int w, int depth);
	void renderingEntities(double dt);
	void showCursor();
	void updatePlayerPosition(sf::Vector2f newPos);
	void setHud();
	void displayHud();
	void pause();
	void endGameManagment();
	void reset();
	int lootManagment(int *proba, int length);
	sf::Vector2f rotateVectorMatrix(sf::Vector2f v, double angle);
	Entity* getInteractedEntity();

	void cleanAllEntitys();
	void bulletExplosion(int nextX, int nextY, int damage);


public:
	StatePlayGame(GameManager * game, Settings settings, std::string mapFilePath = "Map_Example3.txt", int mapSize = 32);
	~StatePlayGame();

	void update(float deltaTime) override;
	void resume();
};

