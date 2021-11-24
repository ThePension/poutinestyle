#pragma once
#include "Entity.h"
#include "AnimatedVertexArray.h"

class Ammo : public Entity
{
public:
	Ammo(int hp, sf::Vector2f pos);
	void draw(sf::RenderTarget& target, Player player, double* ZBuffer, int viewWidth, int viewHeight) override;
	void update(float dt) override;

	AnimatedVertexArray RotatingAnimVA = AnimatedVertexArray("../PoutineStyle/pics/ammo.png", 64, 64, 0, 1);
};

