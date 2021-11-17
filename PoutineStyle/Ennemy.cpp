#include "Ennemy.h"
#include <random>

Ennemy::Ennemy(int hp, sf::Vector2f pos) {
	this->HP = hp;
	this->mapPos = pos;
	srand(time(NULL)); // Randomize seed
}

void Ennemy::draw(sf::RenderTarget& target, Player player, double* ZBuffer, int viewWidth, int viewHeight) {
	if (isShooting) {
		this->shootAnimVA.draw(target, this->mapPos, player, ZBuffer, viewWidth, viewHeight);
	}
	else if(isWalking) { /* Do stuff */ }
	else {
		this->shootAnimVA.draw(target, this->mapPos, player, ZBuffer, viewWidth, viewHeight);
	}
}

void Ennemy::update(float dt) {
	if (isShooting) {
		this->shootAnimVA.update(dt);
		if (shootAnimVA.getIsAnimationOver()) {
			isShooting = false;
		}
	}
}

void Ennemy::shoot(std::list<Bullet*>& bullets, sf::Vector2f direction) {
	if (shootAnimVA.getIsAnimationOver()) {
		isShooting = true;
		
		// Add noise to the bullet direction
		double xNoise = (double)rand() / (RAND_MAX * 10.0); // Between 0 and 0.1
		double yNoise = (double)rand() / (RAND_MAX * 10.0); // Between 0 and 0.1
		sf::Vector2f directionWithNoise = sf::Vector2f(direction.x + xNoise, direction.y + yNoise);

		// Create a bullet
		sf::Vector2f bulletPos = sf::Vector2f((this->mapPos.x), (this->mapPos.y));
		Bullet* bullet = new Bullet(1, bulletPos, directionWithNoise, false);
		bullets.push_back(bullet);
	}
}
