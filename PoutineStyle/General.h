#pragma once
#include "Ennemy.h"
class General : public Ennemy
{
public:
	General(sf::Vector2f pos, int dropNumber = 0);
	std::stack<Bullet*> shoot(sf::Vector2f direction, sf::Vector2f playerPos, char** map) override;
};

