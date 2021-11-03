#pragma once
#include "GameState.h"
#include "Player.h"
#include "Ennemy.h"
#include "Button.h"
#include <list>
#include <numbers>

class StatePlayGame : public GameState
{
private:
	Player player;

	bool isPlayerMoving = false;
	sf::Keyboard::Key keyPressed;
	bool isMapDisplayed = false;

	int mapSize = 32;
	int movingSpeed = 100;
	int movingSpeedSPrint = 150;
	int blockWidth;
	int blockHeight;
	int textureSize = 64;

	int oldMouseX = 0, oldMouseY = 0;

	char** map;

	std::list<Ennemy*> ennemies;	

	std::string mapFileFolder = "Map/"; // Needs to be changed and optimized. (ressource or relative path)
	std::string mapFileName = "Map_Example.txt";

	sf::RectangleShape block;
	sf::CircleShape player_circle;

	sf::Vector2f playerPosition = sf::Vector2f(50.f, 50.f); // Default player position
	sf::Vector2f playerDir = sf::Vector2f(0.f, 0.75f);
	sf::Vector2f planeVec = sf::Vector2f(-0.495f, 0.f); // Must be perpendicular to direction vector (2*atan(0.495/0.75) = 66° FOV)
	sf::Texture wallTextures, spriteTextures, weaponTexture;
	sf::Sprite weaponSprite;

protected:
	void draw() override;
	void handleInput() override;
	void parseMap2D();
	void drawMap2D();
	void drawMap3D();
	sf::Vector2f matrixMult(sf::Vector2f v, double angle);

public:
	StatePlayGame(GameManager * game);
	~StatePlayGame();
	void update(float deltaTime) override;
};

