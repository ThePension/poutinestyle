#include "Uzi.h"
#include "Bullet.h"

Uzi::Uzi() : Weapon(1, Animation(0, 0, 150, 150, 4, "../PoutineStyle/pics/testUzi.png")) {
	weaponSprite.scale(2, 2);
	weaponSprite.setPosition(100, 280);
}

void Uzi::draw(sf::RenderTarget& target, sf::Vector2f playerPos, sf::Vector2f playerDir, sf::Vector2f playerPlaneVec, double* ZBuffer, int viewWidth, int viewHeight) {
	shotgunAnim.draw(target, this->mapPos, playerPos, playerDir, playerPlaneVec, ZBuffer, viewWidth, viewHeight);
}
void Uzi::draw(sf::RenderTarget& target)
{
	target.draw(weaponSprite);
}
void Uzi::update(float dt) {
	if (isShooting) {
		shootAnimation.update(dt);
		if (shootAnimation.isAnimationOver) isShooting = false;
	}
	shootAnimation.ApplyToSprite(weaponSprite);
}

std::stack<Bullet*> Uzi::shoot(sf::Vector2f direction, sf::Vector2f position)
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
		double shotgunDirX = AnimatedVertexArray::map(direction.x, -1, 1, 1.015, 1.02);
		double shotgunDirY = AnimatedVertexArray::map(direction.y, -1, 1, 1.015, 1.02);

		// Create two bullets
		sf::Vector2f bulletPos1 = sf::Vector2f((position.x - 0.5) * (shotgunDirX)+2.0 * direction.x, (position.y - 0.5) * (shotgunDirY)+2.0 * direction.y);
		sf::Vector2f bulletPos2 = sf::Vector2f((position.x - 0.5) * (2.0 - shotgunDirX) + 2.0 * direction.x, (position.y - 0.5) * (2.0 - shotgunDirY) + 2.0 * direction.y);
		Bullet* bullet1 = new Bullet(1, bulletPos1, directionWithNoise, true);
		Bullet* bullet2 = new Bullet(1, bulletPos2, directionWithNoise, true);
		bullets.push(bullet1);
		bullets.push(bullet2);
	}
	return bullets;
}