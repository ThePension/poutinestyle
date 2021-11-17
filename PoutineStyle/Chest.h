#pragma once
#include "Entity.h"
#include "AnimatedVertexArray.h"
class Chest : public Entity
{
private:
	bool isOpening = true; // Must be False by default
	bool isOpen = false;
public:
	Chest(int hp, sf::Vector2f pos);
	void draw(sf::RenderTarget& target, Player player, double* ZBuffer, int viewWidth, int viewHeight) override;
	void update(float dt) override;
	void shoot(std::list<Bullet*>& bullets, sf::Vector2f direction) override;

	AnimatedVertexArray OpeningAnimVA = AnimatedVertexArray("../PoutineStyle/pics/chest.png", 32, 32, 0, 8);
};

