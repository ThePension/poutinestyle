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

	sf::Vector2f startPosition = sf::Vector2f(100.f, 50.f);

	std::string mapFileFolder = "D:\\HE_ARC\\Annee_2\\A2_S1\\INFO\\projet P2 SA\\learning\\TryRaycasting\\TryRaycasting\\"; // Needs to be changed and optimized. (ressource)
	std::string mapFileName = "map_1.txt";
	std::string mapLocation;
	std::string tempText;

	std::ifstream mapFile;

	sf::RenderWindow windowGame;	

	sf::RectangleShape block;
	sf::CircleShape player_circle;

protected:
	void draw() override;
	void handleInput() override;
	void parseMap2D();

public:
	StatePlayGame();
	~StatePlayGame();
	void update() override;
};

