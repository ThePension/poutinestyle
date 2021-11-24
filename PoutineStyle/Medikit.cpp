#include "Medikit.h"

Medikit::Medikit(int hp, sf::Vector2f pos) : Entity(hp, pos) { }

void Medikit::draw(sf::RenderTarget& target, Player player, double* ZBuffer, int viewWidth, int viewHeight)
{
	this->RotatingAnimVA.draw(target, this->mapPos, player, ZBuffer, viewWidth, viewHeight);
}

void Medikit::update(float dt)
{
	this->RotatingAnimVA.update(dt);
}
