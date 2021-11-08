#include "Player.h"
Player::Player() {
	weaponSprite.scale(2, 2);
	weaponSprite.setPosition(700, 1000 - 210);
}
void Player::draw(sf::RenderTarget& target) const {
	target.draw(weaponSprite);
}
void Player::update(float dt) {
	shootAnim.update(dt);
	shootAnim.ApplyToSprite(weaponSprite);
	
}
void Player::shoot() {

}