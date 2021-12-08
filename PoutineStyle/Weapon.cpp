#include "Weapon.h"
#include "Bullet.h"

Weapon::Weapon(int damage, Animation shootAnim) : Entity(1, sf::Vector2f(0.f, 0.f)) {
	this->damage = damage;
	this->shootAnimation = shootAnim;
	shootAnimation.ApplyToSprite(weaponSprite);
}

Weapon::~Weapon() {

}

int Weapon::getCurrentRenderedFrame()
{
	return shootAnimation.getCurrentRenderedFramNum();
}

