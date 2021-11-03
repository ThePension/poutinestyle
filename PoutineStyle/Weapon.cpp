#include "Weapon.h"

Weapon::Weapon()
{

}

Weapon::Weapon(double shootCadency, int damage)
{
	this->shootCadendy = shootCadency;
	this->damage = damage;
}

void Weapon::shoot(sf::Vector2f start, sf::Vector2f direction, GameManager* game)
{
	sf::RectangleShape bullet(sf::Vector2f(10.f, 10.f));
	bullet.setFillColor(sf::Color(100, 250, 50));
	bullet.setPosition(start);

	game->getRenderWindow()->draw(bullet);
}