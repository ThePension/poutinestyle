#include "Pistol.h"
#include "Bullet.h"
Pistol::Pistol() : Weapon(4, Animation(0, 0, 105, 105, 4, "Ressource/Picture/PistolTexture.png")) {
	weaponSprite.scale(2.4, 2.4);
	weaponSprite.setPosition(600, 640);
}

Pistol::~Pistol()
{
	delete this->pistolAnim; this->pistolAnim = nullptr;
}

void Pistol::draw(sf::RenderTarget& target, sf::Vector2f playerPos, sf::Vector2f playerDir, sf::Vector2f playerPlaneVec, double* ZBuffer, int viewWidth, int viewHeight) {
	pistolAnim->draw(target, this->mapPos, playerPos, playerDir, playerPlaneVec, ZBuffer, viewWidth, viewHeight);
}
void Pistol::draw(sf::RenderTarget& target)
{
	target.draw(weaponSprite);
}
void Pistol::update(float dt) {
	if (isShooting) {
		shootAnimation.update(dt);
		if (shootAnimation.isAnimationOver) isShooting = false;
	}
	shootAnimation.ApplyToSprite(weaponSprite);
}

std::stack<Bullet*> Pistol::shoot(sf::Vector2f direction, sf::Vector2f position)
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
		Bullet* bullet = new Bullet(this->bulletDamage, bulletPos, directionWithNoise, true);
		bullets.push(bullet);
	}
	return bullets;
}

