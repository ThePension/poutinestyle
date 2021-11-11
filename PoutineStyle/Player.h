#pragma once

#include "Weapon.h"
#include "Animation.h"
class Player
{
private:
	double posX, posY, cameraAngle;
	Weapon* weapon;
	Animation shootAnim = Animation(0, 0, 105, 105, "../PoutineStyle/pics/gunTexture.png");
	sf::Sprite weaponSprite = sf::Sprite();

public:
	Player();
	Player(double posX, double posY, double cameraAngle);

	void draw(sf::RenderTarget& target) const;
	bool update(float dt, bool shoot);
	bool shoot();
	void takeWeapon(Weapon* weapon);

	sf::Vector2f position = sf::Vector2f(50.f, 50.f); // Default player position
	sf::Vector2f direction = sf::Vector2f(0.f, 0.75f);
	sf::Vector2f planeVec = sf::Vector2f(-0.495f, 0.f); // Must be perpendicular to direction vector (2*atan(0.495/0.75) = 66° FOV)
};

