#pragma once
#include "GameState.h"
#include "Player.h"
#include "Ennemy.h"
#include <list>

class StatePlayGame : public GameState
{
private:
	Player player;
	int mapSize;
	std::list<Ennemy*> ennemies;
	int map[32][32];
public:
	StatePlayGame();
	~StatePlayGame();
	void handleInput() override;
	void update() override;
	void draw() override;
	void parseMap2D();
};

