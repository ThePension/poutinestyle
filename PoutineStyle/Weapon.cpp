#include "Weapon.h"
#include "Bullet.h"

Weapon::Weapon(int bulletDamage, Animation shootAnim) : Entity(1, sf::Vector2f(0.f, 0.f)) {
	this->bulletDamage = bulletDamage;
	this->shootAnimation = shootAnim;
	shootAnimation.ApplyToSprite(weaponSprite);
}

Weapon::~Weapon() {

}