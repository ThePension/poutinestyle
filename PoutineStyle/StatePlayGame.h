#pragma once
#include "GameState.h"
#include "Player.h"
#include "Ennemy.h"
#include <list>

class StatePlayGame : public GameState
{
private:
	Player player;

	int mapSize = 32;
	int windowWidth = 1032;
	int windowHeight = 816;
	int deplacement = 3;
	int indexX = 0, indexY = 0;
	int blockWidth;
	int blockHeight;

	int** map;

	std::list<Ennemy*> ennemies;	

	std::string mapFileFolder = "Map/"; // Needs to be changed and optimized. (ressource or relative path)
	std::string mapFileName = "Map_Example.txt";
	std::string mapLocation;
	std::string tempText;

	std::ifstream mapFile;

	sf::RenderWindow windowGame;

	sf::RectangleShape block;
	sf::CircleShape player_circle;

	sf::Vector2f playerPosition = sf::Vector2f(100.f, 50.f);
	sf::Vector2f playerDir = sf::Vector2f(1.f, 0.f);
	sf::Vector2f plane;

protected:
	void draw() override;
	void handleInput() override;
	void parseMap2D();
	void drawMap2D();
	void drawMap3D();
	sf::Vector2f matrixMult(sf::Vector2f v, double angle);

public:
	StatePlayGame();
	~StatePlayGame();
	void update() override;
};

