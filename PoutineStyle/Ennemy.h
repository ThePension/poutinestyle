#pragma once
#include "Weapon.h"
#include "Animation.h"
#include "Entity.h"
#include "AnimatedVertexArray.h"
class Ennemy : public Entity
{
private:
	int weaponDamage = 1;
	bool isShooting = true;
	bool isWalking = false;
	bool isDying = false;
public:
	Ennemy(int hp, sf::Vector2f pos);
	void draw(sf::RenderTarget& target, Player player, double* ZBuffer) override;
	void update(float dt) override;

	AnimatedVertexArray walkAnimVA = AnimatedVertexArray("../PoutineStyle/pics/ennemyTextures.png", 64, 55, 6, 8);
	AnimatedVertexArray shootAnimVA = AnimatedVertexArray("../PoutineStyle/pics/ennemyTextures.png", 64, 55, 6, 8);
	AnimatedVertexArray dieAnimVA = AnimatedVertexArray("../PoutineStyle/pics/ennemyTextures.png", 64, 55, 6, 8);
};