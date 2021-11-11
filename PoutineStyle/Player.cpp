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

void Player::draw(sf::RenderTarget& target) const
{
	target.draw(weaponSprite);
}

bool Player::update(float dt, bool shoot)
{
	shootAnim.update(dt, shoot);

	if (shootAnim.ApplyToSprite(weaponSprite) < 3 && shoot)
	{
		return true;
	}

	return false;
}

bool Player::shoot()
{
	this->weapon->shoot();
	
	return true;
}
