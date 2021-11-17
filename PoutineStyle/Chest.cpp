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
void Chest::shoot(std::list<Bullet*>& bullets, sf::Vector2f direction) {

}
