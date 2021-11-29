#pragma once
#include "Weapon.h"
#include "Animation.h"
#include "Knife.h"
#include "Pistol.h"
#include "Shotgun.h"
class Bullet;
#include <list>
class Player
{
private:
	Knife * knife;
	Weapon * currentWeapon = nullptr;
	Weapon * secondaryWeapon = nullptr;
	bool isDead = false;
	int live = 3;
	int health = 100;
	int ammunition = 50;
	int currentAmmunition=7;
	int score = 0;

public:
	Player();
	void draw(sf::RenderTarget& target) const;
	void update(float dt);
	std::stack<Bullet*> shoot(sf::Vector2f direction);
	Weapon* getCurrentWeapon() { return this->currentWeapon; }
	Weapon* getSecondaryWeapon() { return this->secondaryWeapon; }
	Weapon* setWeapon(Weapon* w) {
		Weapon* oldWeapon = this->secondaryWeapon;
		this->secondaryWeapon = w;
		this->currentWeapon = w; 
		return oldWeapon;
	}
	void switchWeapon();
	int getLive() {
		return live;
	}

	int getHealth() {
		return health;
	}

	int getAmmunition() {
		return ammunition;
	}

	int getCurrentAmmunition() {
		return currentAmmunition;
	}

	int setCurrentAmmoReloading(int newAmmo) {
		currentAmmunition = newAmmo;
	}

	int getScore() {
		return score;
	}

	void reload();
	void loseLife();
	void increaseLife();
	void increaseAmmo();

	bool dead();

	sf::Vector2f position = sf::Vector2f(50.f, 50.f); // Default player position
	sf::Vector2f direction = sf::Vector2f(0.f, 0.75f);
	sf::Vector2f planeVec = sf::Vector2f(-0.495f, 0.f); // Must be perpendicular to direction vector (2*atan(0.495/0.75) = 66° FOV)
};

