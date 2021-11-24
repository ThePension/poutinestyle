#pragma once
#include "Entity.h"
#include "AnimatedVertexArray.h"
#include "Medikit.h"
class Chest : public Entity
{
private:
	bool isOpening = false; // Must be False by default
	bool isOpen = false;
	Entity* droppedEntity = new Medikit(1, this->mapPos);;
public:
	Chest(int hp, sf::Vector2f pos);
	void draw(sf::RenderTarget& target, Player player, double* ZBuffer, int viewWidth, int viewHeight) override;
	void update(float dt) override;
	void setIsOpening() { isOpening = true; }
	Entity* getDroppedEntity() { return this->droppedEntity; }

	AnimatedVertexArray OpeningAnimVA = AnimatedVertexArray("../PoutineStyle/pics/chest.png", 32, 32, 0, 8);
	AnimatedVertexArray ClosedChestAnimVA = AnimatedVertexArray("../PoutineStyle/pics/chest.png", 32, 32, 0, 1);
};

