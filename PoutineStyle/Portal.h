#pragma once
#include "Entity.h"
#include "AnimatedVertexArray.h"

class Portal : public Entity
{
public:
	Portal(int hp, sf::Vector2f pos);
	void draw(sf::RenderTarget& target, sf::Vector2f playerPos, sf::Vector2f playerDir, sf::Vector2f playerPlaneVec, double* ZBuffer, int viewWidth, int viewHeight) override;
	void update(float dt) override;

	AnimatedVertexArray PortalAnimVA = AnimatedVertexArray("../PoutineStyle/pics/portal.png", 64, 64, 0, 8);
};

