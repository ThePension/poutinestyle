#pragma once
#include "Entity.h"
#include "AnimatedVertexArray.h"
class Bullet : public Entity
{
private:
	int damage = 1;
	bool toRemove = false;
	sf::Vector2f vel;
	bool isPlayerBullet = false;
public:
	Bullet(int hp, sf::Vector2f pos, sf::Vector2f vel, bool isPlayerBullet);
	void draw(sf::RenderTarget& target, Player player, double* ZBuffer, int viewWidth, int viewHeight) override;
	void update(float dt) override;
	void setToRemove(bool b) { this->toRemove = b; }
	bool getToRemove() { return this->toRemove; }
	sf::Vector2f getVelocity() { return this->vel; }
	bool getIsPlayerBullet() { return this->isPlayerBullet; }
	int getDamage() { return this->damage; }
	void shoot(std::list<Bullet*>& bullets, sf::Vector2f direction) override {}
	bool isTravelling = true;
	bool isExplosing = false;
	AnimatedVertexArray travellingAnimVA = AnimatedVertexArray("../PoutineStyle/pics/bullet.png", 64, 64, 0, 1);
	AnimatedVertexArray explosingAnimVA = AnimatedVertexArray("../PoutineStyle/pics/bulletExplosing.png", 64, 64, 0, 7);
};

