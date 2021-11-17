#include "Player.h"
Player::Player()
{
	weaponSprite.scale(1, 1);
	weaponSprite.setPosition(300, 600 - 210);
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

void Player::shoot()
{

}