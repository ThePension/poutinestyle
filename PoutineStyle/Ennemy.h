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
#include <SFML/Audio.hpp>


class Ennemy : public Entity
{
protected:
	bool isShooting = true;
	bool isWalking = false;
	bool isDying = false;
	Entity* droppedEntity = nullptr;
	double shootCooldown = 1.0;
	int oldFrameNum = -1;

public:
	Ennemy(int hp, sf::Vector2f pos, AnimatedVertexArray* shootAnimVA, AnimatedVertexArray* dieAnimVA, int dropNumber = 0);
	~Ennemy() override;
	void draw(sf::RenderTarget& target, sf::Vector2f playerPos, sf::Vector2f playerDir, sf::Vector2f playerPlaneVec, double* ZBuffer, int viewWidth, int viewHeight) override;
	void update(float dt) override;
	virtual std::stack<Bullet*> shoot(sf::Vector2f direction, sf::Vector2f playerPos, char** map, int mapSize) = 0;
	bool isPlayerVisible(sf::Vector2f playerPos, char** map, int mapSize);
	void setIsDying() { this->isDying = true; this->isShooting = false; this->isWalking = false; }
	bool getIsDying() { return this->isDying; }
	Entity* getDroppedEntity() { return this->droppedEntity; }
	int getCurrentRenderedFrame();
	void resetAnimations() { this->shootAnimVA->resetAnimation(); this->dieAnimVA->resetAnimation(); }

	AnimatedVertexArray* shootAnimVA = nullptr; 
	AnimatedVertexArray* dieAnimVA = nullptr;
};

