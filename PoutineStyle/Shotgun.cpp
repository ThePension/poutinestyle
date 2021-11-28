#include "Shotgun.h"
#include "Bullet.h"
Shotgun::Shotgun() : Weapon(1, Animation(0, 0, 64, 64, 11, "../PoutineStyle/pics/shotgun.png")) {
	weaponSprite.scale(2, 2);
	weaponSprite.setPosition(300, 320);
}

void Shotgun::draw(sf::RenderTarget& target, sf::Vector2f playerPos, sf::Vector2f playerDir, sf::Vector2f playerPlaneVec, double* ZBuffer, int viewWidth, int viewHeight) {
	shotgunAnim.draw(target, this->mapPos, playerPos, playerDir, playerPlaneVec, ZBuffer, viewWidth, viewHeight);
}
void Shotgun::draw(sf::RenderTarget& target)
{
	target.draw(weaponSprite);
}
void Shotgun::update(float dt) {
	if (isShooting) {
		shootAnimation.update(dt);
		if (shootAnimation.isAnimationOver) isShooting = false;
	}
	shootAnimation.ApplyToSprite(weaponSprite);
}

std::stack<Bullet*> Shotgun::shoot(sf::Vector2f direction, sf::Vector2f position)
{
	std::stack<Bullet*> bullets;
	if (shootAnimation.isAnimationOver) {
		isShooting = true;
		// Add noise to the bullet direction
		double xNoise = (double)rand() / (RAND_MAX * 10.0); // Between 0 and 0.1
		xNoise = AnimatedVertexArray::map(xNoise, 0, 0.1, -0.1, 0.1);
		double yNoise = (double)rand() / (RAND_MAX * 10.0); // Between 0 and 0.1

		yNoise = AnimatedVertexArray::map(yNoise, 0, 0.1, -0.1, 0.1);
		sf::Vector2f directionWithNoise = sf::Vector2f(direction.x + xNoise / 10, direction.y + yNoise / 10);
		double shotgunDirX = AnimatedVertexArray::map(direction.x, -1, 1, 1.01, 1.02);
		double shotgunDirY = AnimatedVertexArray::map(direction.y, -1, 1, 1.01, 1.02);
		// Create a bullet
		sf::Vector2f bulletPos1 = sf::Vector2f((position.x - 0.5) * (shotgunDirX) + 2.0 * direction.x, (position.y - 0.5) * (shotgunDirY) + 2.0 * direction.y);
		sf::Vector2f bulletPos2 = sf::Vector2f((position.x - 0.5) * (2.0 - shotgunDirX) + 2.0 * direction.x, (position.y - 0.5) * (2.0 - shotgunDirY) + 2.0 * direction.y);
		Bullet* bullet1 = new Bullet(1, bulletPos1, directionWithNoise, true);
		Bullet* bullet2 = new Bullet(1, bulletPos2, directionWithNoise, true);
		bullets.push(bullet1);
		bullets.push(bullet2);
	}
	return bullets;
}
