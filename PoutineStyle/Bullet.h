#pragma once
#include "Entity.h"
#include "AnimatedVertexArray.h"
class Bullet : public Entity
{
private:
	int damage = 1;
	sf::Vector2f vel;
	bool isPlayerBullet = false;
public:
	Bullet(int hp, sf::Vector2f pos, sf::Vector2f vel, bool isPlayerBullet);
	void draw(sf::RenderTarget& target, Player player, double* ZBuffer, int viewWidth, int viewHeight) override;
	void update(float dt) override;
	sf::Vector2f getVelocity() { return this->vel; }
	bool getIsPlayerBullet() { return this->isPlayerBullet; }
	int getDamage() { return this->damage; }
	bool isTravelling = true;
	bool isExplosing = false;
	AnimatedVertexArray travellingAnimVA = AnimatedVertexArray("../PoutineStyle/pics/bullet.png", 64, 64, 0, 1);
	AnimatedVertexArray explosingAnimVA = AnimatedVertexArray("../PoutineStyle/pics/bulletExplosing.png", 64, 64, 0, 7);
};

