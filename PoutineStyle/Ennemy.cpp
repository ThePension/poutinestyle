#include "Ennemy.h"

Ennemy::Ennemy(int hp, sf::Vector2f pos) {
	this->HP = hp;
	this->mapPos = pos;
}

void Ennemy::draw(sf::RenderTarget& target, Player player, double* ZBuffer, int viewWidth, int viewHeight) {
	if (isShooting) {
		this->shootAnimVA.draw(target, this->mapPos, player, ZBuffer, viewWidth, viewHeight);
	}
	else if(isWalking) { /* Do stuff */ }
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
		// Create a bullet
		sf::Vector2f bulletPos = sf::Vector2f((this->mapPos.x), (this->mapPos.y));
		Bullet* bullet = new Bullet(1, bulletPos, direction, false);
		bullets.push_back(bullet);
	}
}
