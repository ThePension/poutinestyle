#include "Weapon.h"
Weapon::Weapon() {
	weaponSprite.scale(1, 1);
	weaponSprite.setPosition(300, 500 - 105);
	shootAnimation.ApplyToSprite(weaponSprite);
}
Weapon::Weapon(double shootCadency, int damage, Animation shootAnim) {
	this->shootCadendy = shootCadency;
	this->damage = damage;
	this->shootAnimation = shootAnim;
	weaponSprite = sf::Sprite();
	shootAnimation.ApplyToSprite(weaponSprite);
}
void Weapon::draw(sf::RenderTarget& target) const{
	target.draw(weaponSprite);
}
void Weapon::update(float dt) {
	shootAnimation.update(dt);
	shootAnimation.ApplyToSprite(weaponSprite);
}