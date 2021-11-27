#include "Chest.h"
Chest::Chest(int hp, sf::Vector2f pos, int dropNumber) : Entity(hp, pos) {
	// Create random entity for drop
	switch (dropNumber)
	{
		case 0: // Ammo pack
			droppedEntity = new Ammo(1, this->mapPos);
			break;
		case 1: // Medikit
			droppedEntity = new Medikit(1, this->mapPos);
			break;
	}
}
void Chest::draw(sf::RenderTarget& target, sf::Vector2f playerPos, sf::Vector2f playerDir, sf::Vector2f playerPlaneVec, double* ZBuffer, int viewWidth, int viewHeight) {
	if (toDraw) {
		if (isOpening) { // Opening chest
			this->OpeningAnimVA.draw(target, this->mapPos, playerPos, playerDir, playerPlaneVec, ZBuffer, viewWidth, viewHeight);
		}
		else if (!isOpen) { // Closed chest
			this->ClosedChestAnimVA.draw(target, this->mapPos, playerPos, playerDir, playerPlaneVec, ZBuffer, viewWidth, viewHeight);
		}
	}
}
void Chest::update(float dt) {
	if (isOpening) { // Opening chest (animation)
		this->OpeningAnimVA.update(dt);
		if (this->OpeningAnimVA.getIsAnimationOver()) {
			this->isOpening = false;
			this->toRemove = true;
		}
	}
}