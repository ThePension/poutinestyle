#include "Ammo.h"

Ammo::Ammo(sf::Vector2f pos) : Entity(1, pos)
{
}

void Ammo::draw(sf::RenderTarget& target, sf::Vector2f playerPos, sf::Vector2f playerDir, sf::Vector2f playerPlaneVec, double* ZBuffer, int viewWidth, int viewHeight)
{
	if(toDraw) this->RotatingAnimVA.draw(target, this->mapPos, playerPos, playerDir, playerPlaneVec, ZBuffer, viewWidth, viewHeight);
}

void Ammo::update(float dt)
{
	
	if(toDraw) this->RotatingAnimVA.update(dt);
}
