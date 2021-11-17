#pragma once
#include "Weapon.h"
#include "Animation.h"
class Bullet;
#include <list>
class Player
{
private:
	Weapon * weapon;
	bool isShooting = false;

public:
	Player();
	void draw(sf::RenderTarget& target) const;
	void update(float dt);
	void shoot(std::list<Bullet*>& bullets, sf::Vector2f direction);

	sf::Vector2f position = sf::Vector2f(50.f, 50.f); // Default player position
	sf::Vector2f direction = sf::Vector2f(0.f, 0.75f);
	sf::Vector2f planeVec = sf::Vector2f(-0.495f, 0.f); // Must be perpendicular to direction vector (2*atan(0.495/0.75) = 66° FOV)
};

