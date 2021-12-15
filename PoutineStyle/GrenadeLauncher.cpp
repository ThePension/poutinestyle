#include "GrenadeLauncher.h"
#include "Bullet.h"
GrenadeLauncher::GrenadeLauncher() : Weapon(4, Animation(0, 0, 209, 128, 4, "../PoutineStyle/pics/GrenadeLauncher.png")) {
	weaponSprite.scale(1, 1);
	weaponSprite.setPosition(300, 320);
}

GrenadeLauncher::~GrenadeLauncher()
{
	delete this->grenadeLauncherAnim; this->grenadeLauncherAnim = nullptr;
}

void GrenadeLauncher::draw(sf::RenderTarget& target, sf::Vector2f playerPos, sf::Vector2f playerDir, sf::Vector2f playerPlaneVec, double* ZBuffer, int viewWidth, int viewHeight) {
	grenadeLauncherAnim->draw(target, this->mapPos, playerPos, playerDir, playerPlaneVec, ZBuffer, viewWidth, viewHeight);
}
void GrenadeLauncher::draw(sf::RenderTarget& target)
{
	target.draw(weaponSprite);
}
void GrenadeLauncher::update(float dt) {
	if (isShooting) {
		shootAnimation.update(dt);
		if (shootAnimation.isAnimationOver) isShooting = false;
	}
	shootAnimation.ApplyToSprite(weaponSprite);
}

std::stack<Bullet*> GrenadeLauncher::shoot(sf::Vector2f direction, sf::Vector2f position)
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

		// Create a bullet
		sf::Vector2f bulletPos = sf::Vector2f(position.x - 0.5 + 2.0 * direction.x, position.y - 0.5 + 2.0 * direction.y);
		Bullet* bullet = new Bullet(this->bulletDamage, bulletPos, directionWithNoise, true, true);
		bullets.push(bullet);
	}
	return bullets;
}


