#include "Ennemy.h"

Ennemy::Ennemy(int hp, sf::Vector2f pos) {
	this->HP = hp;
	this->mapPos = pos;
}

void Ennemy::draw(sf::RenderTarget& target, Player player, double* ZBuffer) {
	if (isShooting) this->shootAnimVA.draw(target, this->mapPos, player, ZBuffer);
	else if(isWalking) { /* Do stuff */ }
}
void Ennemy::update(float dt) {
	if (isShooting) this->shootAnimVA.update(dt);
}
