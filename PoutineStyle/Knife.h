#pragma once
#include "Weapon.h"
class Bullet;
class AnimatedVertexArray;

class Knife : public Weapon
{
public:
	Knife();
	void draw(sf::RenderTarget& target) override;
	void update(float dt) override;
	Bullet * shoot(sf::Vector2f direction, sf::Vector2f position) override;
};

