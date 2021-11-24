#include "Chest.h"
Chest::Chest(int hp, sf::Vector2f pos) {
	this->HP = hp;
	this->mapPos = pos;
}
void Chest::draw(sf::RenderTarget& target, Player player, double* ZBuffer, int viewWidth, int viewHeight) {
	if (isOpening) { // Opening chest
		this->OpeningAnimVA.draw(target, this->mapPos, player, ZBuffer, viewWidth, viewHeight);
	}
	else if (!isOpen) { // Closed chest
		this->ClosedChestAnimVA.draw(target, this->mapPos, player, ZBuffer, viewWidth, viewHeight);
	}
	else if (isOpen) { // Open chest
		// TO DO
	}
}
void Chest::update(float dt) {
	if (isOpening) { // Opening chest (animation)
		this->OpeningAnimVA.update(dt);
		if (this->OpeningAnimVA.getIsAnimationOver()) {
			this->isOpening = false;
		}
	}
	else if (!isOpen) { // Closed chest
		// Nothing to do, no animation for closed chest
	}
	else if (isOpen) { // Open chest
		// TO DO
	}
}