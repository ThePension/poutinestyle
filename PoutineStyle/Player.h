#pragma once
#include "Weapon.h"
#include "Animation.h"
#include "Knife.h"
#include "Pistol.h"
#include "Shotgun.h"
#include "Uzi.h"
#include "Key.h"

class Bullet;
#include <list>
class Player
{
private:
	// Attributes
	Knife * knife;
	Weapon * currentWeapon = nullptr;
	Weapon * secondaryWeapon = nullptr;
	std::list<Key*> playerKeys;
	bool isDead = false;
	int live = 3;
	int health = 100;
	int ammunition = 500;
	int currentAmmunition=70;
	int score = 0;

public:
	// Constructors
	Player();

	// Destructors
	~Player();

	// Methods
	void draw(sf::RenderTarget& target) const;
	void update(float dt);
	std::stack<Bullet*> shoot(sf::Vector2f direction);

	std::stack<Bullet*> burstShooting(sf::Vector2f direction);

	void reload();
	void loseLife();
	void increaseLife();
	void increaseAmmo();
	void switchWeapon();
	void clearKeys();

	// Setters
	Weapon* setWeapon(Weapon* w);
	void addKey(Key* key) { this->playerKeys.push_back(key); }

	// Getters
	std::list<Key*> getPlayerKeys() { return this->playerKeys; }
	int getLive() { return live; }
	int getHealth() { return health; }
	int getAmmunition() { return ammunition; }
	int getCurrentAmmunition() { return currentAmmunition; }
	int setCurrentAmmoReloading(int newAmmo) { currentAmmunition = newAmmo; }
	int getScore() { return score; }
	Weapon* getCurrentWeapon() { return this->currentWeapon; }
	Weapon* getSecondaryWeapon() { return this->secondaryWeapon; }
	bool getIsDead() { return this->isDead; }

	sf::Vector2f position = sf::Vector2f(50.f, 50.f); // Default player position
	sf::Vector2f direction = sf::Vector2f(0.f, 0.75f);
	sf::Vector2f planeVec = sf::Vector2f(-0.495f, 0.f); // Must be perpendicular to direction vector (2*atan(0.495/0.75) = 66° FOV)

};

