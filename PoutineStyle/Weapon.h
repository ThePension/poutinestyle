#pragma once
#include "Animation.h"
#include "AnimatedVertexArray.h"
#include "Entity.h"
#include <stack>
class Bullet;

class Weapon : public Entity
{
protected:
	sf::Sprite weaponSprite = sf::Sprite();
	Animation shootAnimation;
	int damage = 1;
	bool isShooting = false;
	bool isEntity = false;
	int oldFrameNum = -1;

public:
	Weapon(int damage, Animation shootAnim = Animation(0, 0, 105, 105, 4, "../PoutineStyle/pics/gunTexture.png"));
	virtual ~Weapon() override = 0;
	virtual void draw(sf::RenderTarget& target, sf::Vector2f playerPos, sf::Vector2f playerDir, sf::Vector2f playerPlaneVec, double* ZBuffer, int viewWidth, int viewHeight) = 0;
	virtual void draw(sf::RenderTarget& target) = 0;
	virtual void update(float dt) = 0;
	virtual std::stack<Bullet*> shoot(sf::Vector2f direction, sf::Vector2f position) = 0;
	Animation getShootAnimation() { return this->shootAnimation; }
	int getDamage() { return this->damage; }
	bool getIsEntity() { return this->isEntity; }
	void setIsEntity(bool b) { this->isEntity = b; }
	int getCurrentRenderedFrame();

};