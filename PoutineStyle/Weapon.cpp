#include "Weapon.h"
Weapon::Weapon() {
	weaponSprite.scale(1, 1);
	weaponSprite.setPosition(300, 500 - 105);
}
Weapon::Weapon(double shootCadency, int damage, Animation shootAnim) {
	this->shootCadendy = shootCadency;
	this->damage = damage;
	weaponSprite = sf::Sprite();
	this->shootAnimation = shootAnim;
}
void Weapon::draw(sf::RenderTarget& target) const{
	target.draw(weaponSprite);
}
void Weapon::update(float dt) {
	shootAnimation.update(dt);
	shootAnimation.ApplyToSprite(weaponSprite);
}