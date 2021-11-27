#include "Key.h"

Key::Key(int hp, sf::Vector2f pos, AnimatedVertexArray anim, char code) : Entity(hp, pos)
{
	this->keyAnimVertexArray = anim;
	this->code = code;
}

void Key::draw(sf::RenderTarget& target, sf::Vector2f playerPos, sf::Vector2f playerDir, sf::Vector2f playerPlaneVec, double* ZBuffer, int viewWidth, int viewHeight)
{
	if (toDraw) this->keyAnimVertexArray.draw(target, this->mapPos, playerPos, playerDir, playerPlaneVec, ZBuffer, viewWidth, viewHeight);
}

void Key::update(float dt)
{
	if (toDraw) this->keyAnimVertexArray.update(dt);
}
