#pragma once

#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include <iostream>

class Weapon
{
	private:
		double shootCadendy;
		int damage;

	public:
		Weapon();
		Weapon(double shootCadency, int damage);

		void shoot(sf::Vector2f start, sf::Vector2f direction, GameManager* game);
};

