#pragma once
#include "Ennemy.h"
class Guard : public Ennemy
{
public:
	Guard(sf::Vector2f pos, int dropNumber = 0);
	std::stack<Bullet*> shoot(sf::Vector2f direction, sf::Vector2f playerPos, char** map) override;
};

