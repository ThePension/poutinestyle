#include "Chest.h"

Chest::Chest(sf::Vector2f pos, int dropNumber) : Entity(1, pos, true) {
	// Create random entity for drop
	switch (dropNumber)
	{
		case 1: // pistolet 25%
			droppedEntity = new Pistol();
			droppedEntity->mapPos = this->mapPos;
			break;
		case 2: // fusil à pompe 15%
			droppedEntity = new Shotgun();
			droppedEntity->mapPos = this->mapPos;
			break;
		case 3: // fusil mitrailleur 2%
			droppedEntity = new Shotgun();
			droppedEntity->mapPos = this->mapPos;
			break;
		case 4: // munition 35%
			droppedEntity = new Ammo(this->mapPos);
			break;
		case 5: // soin 20%
			droppedEntity = new Medikit(this->mapPos);
			break;
		case 6: // HP 3%
			droppedEntity = new Medikit(this->mapPos);
			break;
	}
}
Chest::~Chest()
{
	delete this->ClosedChestAnimVA; this->ClosedChestAnimVA = nullptr;
	delete this->OpeningAnimVA; this->OpeningAnimVA = nullptr;
}
void Chest::draw(sf::RenderTarget& target, sf::Vector2f playerPos, sf::Vector2f playerDir, sf::Vector2f playerPlaneVec, double* ZBuffer, int viewWidth, int viewHeight) {
	if (toDraw) {
		if (isOpening) { // Opening chest
			this->OpeningAnimVA->draw(target, this->mapPos, playerPos, playerDir, playerPlaneVec, ZBuffer, viewWidth, viewHeight);
		}
		else if (!isOpen) { // Closed chest
			this->ClosedChestAnimVA->draw(target, this->mapPos, playerPos, playerDir, playerPlaneVec, ZBuffer, viewWidth, viewHeight);
		}
	}
}
void Chest::update(float dt) {
	if (isOpening) { // Opening chest (animation)
		this->OpeningAnimVA->update(dt);
		if (this->OpeningAnimVA->getIsAnimationOver()) {
			this->isOpening = false;
			this->toRemove = true;
		}
	}
}