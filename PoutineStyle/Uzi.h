#pragma once
#include "Weapon.h"
class Bullet;
#include "AnimatedVertexArray.h"

class Uzi : public Weapon
{
private:
	AnimatedVertexArray shotgunAnim = AnimatedVertexArray("../PoutineStyle/pics/shotgunStatic.png", 64, 64, 0, 1);
public:
	Uzi();
	void draw(sf::RenderTarget& target, sf::Vector2f playerPos, sf::Vector2f playerDir, sf::Vector2f playerPlaneVec, double* ZBuffer, int viewWidth, int viewHeight) override;
	void draw(sf::RenderTarget& target) override;
	void update(float dt) override;
	std::stack<Bullet*> shoot(sf::Vector2f direction, sf::Vector2f position) override;
};