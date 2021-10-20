#pragma once
#include "Weapon.h"
class Ennemy
{
private:
	int PV;
	Weapon* weapon;
public:
	Ennemy();
	Ennemy(int pv);
};