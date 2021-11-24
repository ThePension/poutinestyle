#include "Bullet.h"
Bullet::Bullet(int hp, sf::Vector2f pos, sf::Vector2f vel, bool isPlayerBullet) : Entity(hp, pos) {
	this->vel = vel;
	this->isPlayerBullet = isPlayerBullet;
}
void Bullet::draw(sf::RenderTarget& target, Player player, double* ZBuffer, int viewWidth, int viewHeight) {
	if (isTravelling) {
		this->travellingAnimVA.draw(target, this->mapPos, player, ZBuffer, viewWidth, viewHeight);
	}
	else if(isExplosing) {
		this->explosingAnimVA.draw(target, this->mapPos, player, ZBuffer, viewWidth, viewHeight);
	}
}
void Bullet::update(float dt) {
	if (isTravelling) {
		this->travellingAnimVA.update(dt);
		this->mapPos += this->vel * dt * 10.f;
	}
	else if (isExplosing)
	{
		if (this->explosingAnimVA.getIsAnimationOver()) this->toRemove = true;
		else this->explosingAnimVA.update(dt);
	}
}

