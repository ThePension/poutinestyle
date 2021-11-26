#include "Weapon.h"
#include "Bullet.h"

Weapon::Weapon(int damage, Animation shootAnim) {
	this->damage = damage;
	this->shootAnimation = shootAnim;
	shootAnimation.ApplyToSprite(weaponSprite);
}