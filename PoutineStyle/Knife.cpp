#include "Knife.h"
#include "Bullet.h"
Knife::Knife() : Weapon(1, Animation(0, 0, 64, 64, "../PoutineStyle/pics/knife.png")) {
	weaponSprite.scale(2, 2);
	weaponSprite.setPosition(300, 320);
}

void Knife::draw(sf::RenderTarget& target) {
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
		/*
		// Add noise to the bullet direction
		double xNoise = (double)rand() / (RAND_MAX * 10.0); // Between 0 and 0.1
		xNoise = AnimatedVertexArray::map(xNoise, 0, 0.1, -0.1, 0.1);
		double yNoise = (double)rand() / (RAND_MAX * 10.0); // Between 0 and 0.1

		yNoise = AnimatedVertexArray::map(yNoise, 0, 0.1, -0.1, 0.1);
		sf::Vector2f directionWithNoise = sf::Vector2f(direction.x + xNoise / 10, direction.y + yNoise / 10);

		// Create a bullet
		sf::Vector2f bulletPos = sf::Vector2f(position.x - 0.5 + 2.0 * direction.x, position.y - 0.5 + 2.0 * direction.y);
		Bullet* bullet = new Bullet(1, bulletPos, directionWithNoise, true);

		return bullet;*/
		return nullptr;
	}
	return nullptr;
}
