#pragma once
#include "Weapon.h"
#include "Animation.h"
#include "Entity.h"
#include "AnimatedVertexArray.h"
#include "Bullet.h"
#include "Weapon.h"
#include "Medikit.h"
#include "Ammo.h"
#include "Pistol.h"
#include "Shotgun.h"


class Ennemy : public Entity
{
protected:
	bool isShooting = true;
	bool isWalking = false;
	bool isDying = false;
	Entity* droppedEntity = nullptr;
	double shootCooldown = 1.0;
public:
	Ennemy(int hp, sf::Vector2f pos, AnimatedVertexArray shootAnimVA, AnimatedVertexArray dieAnimVA, int dropNumber = 0);
	void draw(sf::RenderTarget& target, sf::Vector2f playerPos, sf::Vector2f playerDir, sf::Vector2f playerPlaneVec, double* ZBuffer, int viewWidth, int viewHeight) override;
	void update(float dt) override;
	virtual Bullet * shoot(sf::Vector2f direction, sf::Vector2f playerPos, char** map) = 0;
	bool isPlayerVisible(sf::Vector2f playerPos, char** map);
	void setIsDying() { this->isDying = true; this->isShooting = false; this->isWalking = false; }
	bool getIsDying() { return this->isDying; }
	Entity* getDroppedEntity() { return this->droppedEntity; }

	// AnimatedVertexArray walkAnimVA = AnimatedVertexArray("../PoutineStyle/pics/ennemyTextures.png", 64, 64, 0, 8);
	AnimatedVertexArray shootAnimVA = AnimatedVertexArray("../PoutineStyle/pics/shootingEnnemy.png", 64, 64, 0, 5, 0.3);
	AnimatedVertexArray dieAnimVA = AnimatedVertexArray("../PoutineStyle/pics/dyingEnnemy.png", 64, 64, 0, 4, 0.3);
};