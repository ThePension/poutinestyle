#pragma once
#include "Entity.h"
#include "AnimatedVertexArray.h"

class Key : public Entity
{
private:
	char code = 'd';
public:
	AnimatedVertexArray* keyAnimVertexArray;
	Key(sf::Vector2f pos, AnimatedVertexArray* anim, char code);
	~Key() override;
	void draw(sf::RenderTarget& target, sf::Vector2f playerPos, sf::Vector2f playerDir, sf::Vector2f playerPlaneVec, double* ZBuffer, int viewWidth, int viewHeight) override;
	void update(float dt) override;
	char getKeyCode() { return this->code; }
	sf::Texture getTexture() { return this->keyAnimVertexArray->getTexture(); }
	sf::Sprite getFirstSprite() { return this->keyAnimVertexArray->getFirstSprite(); }
};

