#include "Wall.h"

Wall::Wall(sf::Vector2f pos, int frameCount, int y, bool isDestructible, double frameDuration) : Entity(1, pos)
{
	this->frameCount = frameCount;
	this->frameDuration = frameDuration;
	this->currentTextureCoordinates.y = y;
	this->isDestructible = isDestructible;
}

Wall::~Wall()
{

}

void Wall::draw(sf::RenderTarget& target, sf::Vector2f playerPos, sf::Vector2f playerDir, sf::Vector2f playerPlaneVec, double* ZBuffer, int viewWidth, int viewHeight)
{
	// Nothing to do here : Walls are drawn in StatePlayGame class
}

void Wall::update(float dt)
{
	isAnimationOver = false;
	time += dt;
	while (time >= frameDuration)
	{
		time -= frameDuration;
		if (++currentTextureCoordinates.x >= frameCount) {
			currentTextureCoordinates.x = 0;
			isAnimationOver = true;
		}
	}
}
