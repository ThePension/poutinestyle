#include "Chest.h"

Chest::Chest(sf::Vector2f pos, int dropNumber) : Entity(1, pos, true) {
	// Create random entity for drop
	switch (dropNumber)
	{
		case 1: // shotgun 40%
			droppedEntity = new Shotgun();
			droppedEntity->mapPos = this->mapPos;
			break;
		case 2: // uzi 40%
			droppedEntity = new Uzi();
			droppedEntity->mapPos = this->mapPos;
			break;
		case 3: // bazooka 20%
			droppedEntity = new GrenadeLauncher();
			droppedEntity->mapPos = this->mapPos;
			break;
	}

	openingChestBuffer.loadFromFile("../PoutineStyle/Sound/ChestOpening.wav");
	openingChest.setBuffer(openingChestBuffer);
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

void Chest::setIsOpening()
{
	isOpening = true;
	openingChest.play();
}
