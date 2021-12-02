#pragma once
#include "Entity.h"
#include "AnimatedVertexArray.h"

class Ammo : public Entity
{
public:
	Ammo(sf::Vector2f pos);
	void draw(sf::RenderTarget& target, sf::Vector2f playerPos, sf::Vector2f playerDir, sf::Vector2f playerPlaneVec, double* ZBuffer, int viewWidth, int viewHeight) override;
	void update(float dt) override;

	AnimatedVertexArray RotatingAnimVA = AnimatedVertexArray("../PoutineStyle/pics/ammo.png", 64, 64, 0, 1);
};

