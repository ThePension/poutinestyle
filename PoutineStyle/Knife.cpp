#include "Knife.h"
#include "Bullet.h"
Knife::Knife() : Weapon(1, Animation(0, 0, 64, 64, 8, "Ressource/Picture/Knife.png")) 
{
	weaponSprite.scale(4, 4);
	weaponSprite.setPosition(600, 640);
}

void Knife::draw(sf::RenderTarget& target, sf::Vector2f playerPos, sf::Vector2f playerDir, sf::Vector2f playerPlaneVec, double* ZBuffer, int viewWidth, int viewHeight) {}

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

std::stack<Bullet*> Knife::shoot(sf::Vector2f direction, sf::Vector2f position)
{
	std::stack<Bullet*> bullets;
	if (shootAnimation.isAnimationOver) {
		isShooting = true;
	}
	return bullets;
}
