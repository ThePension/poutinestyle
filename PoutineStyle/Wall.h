#pragma once
#include "Entity.h"

class Wall : public Entity
{
public:
	Wall(sf::Vector2f pos, int frameCount, int y, double frameDuration, bool isDestructible = false);
	~Wall();
	void draw(sf::RenderTarget& target, sf::Vector2f playerPos, sf::Vector2f playerDir, sf::Vector2f playerPlaneVec, double* ZBuffer, int viewWidth, int viewHeight);
	virtual void update(float dt);
	sf::Vector2i getCurrentTextureCoordinates() { return this->currentTextureCoordinates; }
	bool getIsTransparent() { return this->isTransparent; }

protected:
	sf::Vector2i currentTextureCoordinates = sf::Vector2i(0, 0);
	double time = 0.0;
	double frameDuration;
	bool isAnimationOver = false;
	int frameCount = 0;
	bool isDestructible = false;
	bool isTransparent = false;
};

