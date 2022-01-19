#pragma once
#include "Weapon.h"
class Bullet;
#include "AnimatedVertexArray.h"

class Pistol : public Weapon
{
private:
	AnimatedVertexArray* pistolAnim = new AnimatedVertexArray("Ressource/Picture/PistolStatic.png", 64, 64, 0, 1);
public:
	Pistol();
	~Pistol() override;
	void draw(sf::RenderTarget& target, sf::Vector2f playerPos, sf::Vector2f playerDir, sf::Vector2f playerPlaneVec, double* ZBuffer, int viewWidth, int viewHeight) override;
	void draw(sf::RenderTarget& target) override;
	void update(float dt) override;
	std::stack<Bullet*> shoot(sf::Vector2f direction, sf::Vector2f position) override;
};

