#pragma once
#include "Entity.h"
#include "AnimatedVertexArray.h"

class Key : public Entity
{
private:
	char code = 'd';
public:
	AnimatedVertexArray keyAnimVertexArray = AnimatedVertexArray("../PoutineStyle/pics/key.png", 64, 64, 0, 1);
	Key(int hp, sf::Vector2f pos, AnimatedVertexArray anim, char code);
	void draw(sf::RenderTarget& target, Player player, double* ZBuffer, int viewWidth, int viewHeight) override;
	void update(float dt) override;
	char getKeyCode() { return this->code; }
};
