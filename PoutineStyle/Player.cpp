#include "Player.h"

Player::Player()
{
	weaponSprite.scale(2, 2);
	weaponSprite.setPosition(700, 1000 - 210);
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

void Player::draw(sf::RenderTarget& target) const
{
	target.draw(weaponSprite);
}

void Player::update(float dt)
{
	shootAnim.update(dt);
	shootAnim.ApplyToSprite(weaponSprite);
	
}

void Player::shoot()
{

}
