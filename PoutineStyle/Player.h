#pragma once
#include "Weapon.h"
#include "Animation.h"
#include "Knife.h"
#include "Pistol.h"
#include "Shotgun.h"
#include "GrenadeLauncher.h"
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
	int ammunition = 0;
	int currentAmmunition= 0; // modify
	int chargerCapacity = 0; // new
	int nbChargers = 4; // new
	int score = 0;

public:
	// Constructors
	Player();
	Player(int live, int ammunition);

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
	void removeKey(Key* key) { this->playerKeys.remove(key); }
	void increaseScore(int bonus) { this->score += bonus; }

	// Getters
	std::list<Key*> getPlayerKeys() { return this->playerKeys; }
	int getScore() { return this->score; }
	int getLive() { return this->live; }
	int getHealth() { return this->health; }
	int getAmmunition() { return this->ammunition; }
	int getCurrentAmmunition() { return this->currentAmmunition; }
	int setCurrentAmmoReloading(int newAmmo) { currentAmmunition = newAmmo; }
	Weapon* getCurrentWeapon() { return this->currentWeapon; }
	Weapon* getSecondaryWeapon() { return this->secondaryWeapon; }
	bool getIsDead() { return this->isDead; }

	sf::Vector2f position = sf::Vector2f(50.f, 50.f); // Default player position
	sf::Vector2f direction = sf::Vector2f(0.f, 0.75f);
	sf::Vector2f planeVec = sf::Vector2f(-0.495f, 0.f); // Must be perpendicular to direction vector (2*atan(0.495/0.75) = 66° FOV)

};

