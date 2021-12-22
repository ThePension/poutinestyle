#pragma once
#include "Entity.h"
#include "AnimatedVertexArray.h"

class Medikit : public Entity
{
public:
	Medikit(sf::Vector2f pos);
	~Medikit() override;
	void draw(sf::RenderTarget& target, sf::Vector2f playerPos, sf::Vector2f playerDir, sf::Vector2f playerPlaneVec, double* ZBuffer, int viewWidth, int viewHeight) override;
	void update(float dt) override;

	AnimatedVertexArray* RotatingAnimVA = new AnimatedVertexArray("../PoutineStyle/pics/medikit.png", 128, 128, 0, 1);
};