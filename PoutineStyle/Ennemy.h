#pragma once
#include "Weapon.h"
#include "Animation.h"
#include "Entity.h"
#include "AnimatedVertexArray.h"
#include "Bullet.h"
#include "Weapon.h"
class Ennemy : public Entity
{
private:
	bool isShooting = true;
	bool isWalking = false;
	bool isDying = false;
public:
	Ennemy(int hp, sf::Vector2f pos);
	void draw(sf::RenderTarget& target, Player player, double* ZBuffer, int viewWidth, int viewHeight) override;
	void update(float dt) override;
	void shoot(std::list<Bullet*>& bullets, sf::Vector2f direction) override;

	AnimatedVertexArray walkAnimVA = AnimatedVertexArray("../PoutineStyle/pics/ennemyTextures.png", 64, 55, 6, 8);
	AnimatedVertexArray shootAnimVA = AnimatedVertexArray("../PoutineStyle/pics/ennemyTextures.png", 64, 55, 6, 8);
	AnimatedVertexArray dieAnimVA = AnimatedVertexArray("../PoutineStyle/pics/ennemyTextures.png", 64, 55, 6, 8);
};