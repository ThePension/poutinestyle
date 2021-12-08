#pragma once
#include "Entity.h"

class Wall : public Entity
{
public:
	Wall(sf::Vector2f pos, int frameCount, int y, bool isDestructible, bool isDoor = false, double frameDuration = 0.1);
	~Wall();
	void draw(sf::RenderTarget& target, sf::Vector2f playerPos, sf::Vector2f playerDir, sf::Vector2f playerPlaneVec, double* ZBuffer, int viewWidth, int viewHeight);
	void update(float dt);
	void setOpening() { this->isOpening = true; }
	sf::Vector2i getCurrentTextureCoordinates() { return this->currentTextureCoordinates; }

private:
	sf::Vector2i currentTextureCoordinates = sf::Vector2i(0, 0);
	double time = 0.0;
	double frameDuration = 0.1;
	bool isAnimationOver = false;
	int frameCount = 0;
	bool isDestructible = false;
	bool isDoor = false;
	bool isOpening = false;

};

