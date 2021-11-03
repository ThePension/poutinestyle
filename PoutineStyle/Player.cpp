#include "Player.h"

Player::Player()
{

}

Player::Player(double posX, double posY, double cameraAngle)
{
	this->posX = posX;
	this->posY = posY;
	this->cameraAngle = cameraAngle;
}

void Player::takeWeapon(Weapon* weapon)
{
	this->weapon = weapon;
}

void Player::useWeapon(sf::Vector2f start, sf::Vector2f direction, GameManager* game)
{
	this->weapon->shoot(start, direction, game);
}
