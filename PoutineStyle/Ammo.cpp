#include "Ammo.h"

Ammo::Ammo(int hp, sf::Vector2f pos) : Entity(hp, pos)
{
}

void Ammo::draw(sf::RenderTarget& target, Player player, double* ZBuffer, int viewWidth, int viewHeight)
{
	if(toDraw) this->RotatingAnimVA.draw(target, this->mapPos, player, ZBuffer, viewWidth, viewHeight);
}

void Ammo::update(float dt)
{
	
	if(toDraw) this->RotatingAnimVA.update(dt);
}
