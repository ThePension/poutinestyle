#pragma once
#include "Animation.h"
// #include "Entity.h"
class Bullet;
class AnimatedVertexArray;

class Weapon
{
protected:
	sf::Sprite weaponSprite = sf::Sprite();
	Animation shootAnimation;
	int damage = 1;
	bool isShooting = false;

public:
	Weapon(int damage, Animation shootAnim = Animation(0, 0, 105, 105, "../PoutineStyle/pics/gunTexture.png"));
	virtual void draw(sf::RenderTarget& target) = 0;
	virtual void update(float dt) = 0;
	virtual Bullet* shoot(sf::Vector2f direction, sf::Vector2f position) = 0;
	Animation getShootAnimation() { return this->shootAnimation; }
	int getDamage() { return this->damage; }
};