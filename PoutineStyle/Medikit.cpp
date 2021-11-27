#include "Medikit.h"

Medikit::Medikit(int hp, sf::Vector2f pos) : Entity(hp, pos) { }

void Medikit::draw(sf::RenderTarget& target, sf::Vector2f playerPos, sf::Vector2f playerDir, sf::Vector2f playerPlaneVec, double* ZBuffer, int viewWidth, int viewHeight)
{
	if (toDraw) this->RotatingAnimVA.draw(target, this->mapPos, playerPos, playerDir, playerPlaneVec, ZBuffer, viewWidth, viewHeight);
}

void Medikit::update(float dt)
{
	if (toDraw) this->RotatingAnimVA.update(dt);
}
