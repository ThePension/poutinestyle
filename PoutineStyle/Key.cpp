#include "Key.h"

Key::Key(int hp, sf::Vector2f pos, AnimatedVertexArray anim, char code) : Entity(hp, pos)
{
	this->keyAnimVertexArray = anim;
	this->code = code;
}

void Key::draw(sf::RenderTarget& target, Player player, double* ZBuffer, int viewWidth, int viewHeight)
{
	if (toDraw) this->keyAnimVertexArray.draw(target, this->mapPos, player, ZBuffer, viewWidth, viewHeight);
}

void Key::update(float dt)
{
	if (toDraw) this->keyAnimVertexArray.update(dt);
}
