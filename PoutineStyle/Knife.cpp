#include "Knife.h"
#include "Bullet.h"
Knife::Knife() : Weapon(1, Animation(0, 0, 64, 64, "../PoutineStyle/pics/knife.png")) {
	weaponSprite.scale(2, 2);
	weaponSprite.setPosition(300, 320);
}

void Knife::draw(sf::RenderTarget& target, sf::Vector2f playerPos, sf::Vector2f playerDir, sf::Vector2f playerPlaneVec, double* ZBuffer, int viewWidth, int viewHeight) {
	// To do
}

void Knife::draw(sf::RenderTarget& target)
{
	target.draw(weaponSprite);
}

void Knife::update(float dt) {
	if (isShooting) {
		shootAnimation.update(dt);
		if (shootAnimation.isAnimationOver) isShooting = false;
	}
	shootAnimation.ApplyToSprite(weaponSprite);
}

Bullet * Knife::shoot(sf::Vector2f direction, sf::Vector2f position)
{
	if (shootAnimation.isAnimationOver) {
		isShooting = true;
		return nullptr;
	}
	return nullptr;
}
