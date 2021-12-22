#pragma once
#include "Entity.h"
#include "AnimatedVertexArray.h"
#include "Medikit.h"
#include "Pistol.h"
#include "Shotgun.h"
#include "Ammo.h"

class Chest : public Entity
{
private:
	bool isOpening = false; // Must be False by default
	bool isOpen = false;
	Entity* droppedEntity = nullptr;
public:
	Chest(sf::Vector2f pos, int dropNumber);
	~Chest() override;
	void draw(sf::RenderTarget& target, sf::Vector2f playerPos, sf::Vector2f playerDir, sf::Vector2f playerPlaneVec, double* ZBuffer, int viewWidth, int viewHeight) override;
	void update(float dt) override;
	void setIsOpening() { isOpening = true; }
	Entity* getDroppedEntity() { return this->droppedEntity; }

	AnimatedVertexArray* OpeningAnimVA = new AnimatedVertexArray("../PoutineStyle/pics/chest.png", 32, 32, 0, 8);
	AnimatedVertexArray* ClosedChestAnimVA = new AnimatedVertexArray("../PoutineStyle/pics/chest.png", 32, 32, 0, 1);
};

