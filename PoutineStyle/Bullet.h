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
	~Bullet() override;
	void draw(sf::RenderTarget& target, sf::Vector2f playerPos, sf::Vector2f playerDir, sf::Vector2f playerPlaneVec, double* ZBuffer, int viewWidth, int viewHeight) override;
	void update(float dt) override;
	sf::Vector2f getVelocity() { return this->vel; }
	bool getIsPlayerBullet() { return this->isPlayerBullet; }
	int getDamage() { return this->damage; }
	bool isTravelling = true;
	bool isExplosing = false;
	AnimatedVertexArray* travellingAnimVA = new AnimatedVertexArray("../PoutineStyle/pics/bullet.png", 64, 64, 0, 1);
	AnimatedVertexArray* explosingAnimVA = new AnimatedVertexArray("../PoutineStyle/pics/bulletExplosing.png", 64, 64, 0, 7);
};

