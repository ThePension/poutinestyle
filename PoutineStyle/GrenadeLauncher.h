#pragma once
#include "Weapon.h"
class Bullet;
#include "AnimatedVertexArray.h"

class GrenadeLauncher : public Weapon
{
private:
	AnimatedVertexArray* grenadeLauncherAnim = new AnimatedVertexArray("../PoutineStyle/pics/GrenadeLauncher.png", 64, 64, 2, 1);
public:
	GrenadeLauncher();
	~GrenadeLauncher() override;
	void draw(sf::RenderTarget& target, sf::Vector2f playerPos, sf::Vector2f playerDir, sf::Vector2f playerPlaneVec, double* ZBuffer, int viewWidth, int viewHeight) override;
	void draw(sf::RenderTarget& target) override;
	void update(float dt) override;
	std::stack<Bullet*> shoot(sf::Vector2f direction, sf::Vector2f position) override;
};



