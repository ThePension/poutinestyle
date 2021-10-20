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
};

