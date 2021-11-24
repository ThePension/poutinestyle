#include "Ammo.h"

Ammo::Ammo(int hp, sf::Vector2f pos) : Entity(hp, pos)
{
}

void Ammo::draw(sf::RenderTarget& target, Player player, double* ZBuffer, int viewWidth, int viewHeight)
{
	this->RotatingAnimVA.draw(target, this->mapPos, player, ZBuffer, viewWidth, viewHeight);
}

void Ammo::update(float dt)
{
	this->RotatingAnimVA.update(dt);
}
