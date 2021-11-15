#include "Player.h"
#include "Bullet.h"
Player::Player() {
	weaponSprite.scale(1, 1);
	weaponSprite.setPosition(300, 500 - 105);
}
void Player::draw(sf::RenderTarget& target) const {
	target.draw(weaponSprite);
}
void Player::update(float dt) {
	if (isShooting) {
		shootAnim.update(dt);
		shootAnim.ApplyToSprite(weaponSprite);
		if (shootAnim.isAnimationOver) isShooting = false;
	}	
}
void Player::shoot(std::list<Bullet*>& bullets, sf::Vector2f direction) {
	if (shootAnim.isAnimationOver) {
		isShooting = true;
		// Create a bullet
		sf::Vector2f bulletPos = sf::Vector2f(this->position.x - 0.5 + 2*this->direction.x, this->position.y - 0.5 + 2*this->direction.y);
		Bullet* bullet = new Bullet(1, bulletPos, direction, true);
		bullets.push_back(bullet);
	}
}