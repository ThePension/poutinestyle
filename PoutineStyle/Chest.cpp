#include "Chest.h"
Chest::Chest(int hp, sf::Vector2f pos) {
	this->HP = hp;
	this->mapPos = pos;
}
void Chest::draw(sf::RenderTarget& target, Player player, double* ZBuffer) {
	if (isOpening) { // Opening chest
		this->OpeningAnimVA.draw(target, this->mapPos, player, ZBuffer);
	}
	else if (!isOpen) { // Closed chest
		// TO DO
	}
	else if (isOpen) { // Open chest
		// TO DO
	}
}
void Chest::update(float dt) {
	if (isOpening) { // Opening chest (animation)
		this->OpeningAnimVA.update(dt);
	}
	else if (!isOpen) { // Closed chest
		// TO DO
	}
	else if (isOpen) { // Open chest
		// TO DO
	}
}
