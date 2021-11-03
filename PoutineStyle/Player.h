#pragma once

#include "Weapon.h"

class Player
{
	private:
		double posX, posY, cameraAngle;
		Weapon* weapon;

	public:
		Player();
		Player(double posX, double posY, double cameraAngle);

		void takeWeapon(Weapon* weapon);
		void useWeapon(sf::Vector2f start, sf::Vector2f direction, GameManager* game);

		//bool shoot(sf::Vector2f start, sf::Vector2f direction);
};

