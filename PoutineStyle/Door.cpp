#include "Door.h"

Door::Door(sf::Vector2f pos, int frameCount, int y, double frameDuration, bool isDestructible, bool isSecretPassage, bool isLift)
	: Wall(pos, frameCount, y, frameDuration, isDestructible)
{
	this->isSecretPassage = isSecretPassage;
	this->isLift = isLift;
	this->isTransparent = false;
}

Door::~Door()
{
	// Nothing to delete
}

void Door::update(float dt)
{
	if (isOpening) {
		isAnimationOver = false;
		time += dt;
		while (time >= frameDuration)
		{
			time -= frameDuration;
			if (++currentTextureCoordinates.x >= frameCount) {
				this->toRemove = true;
				currentTextureCoordinates.x = 0;
				isAnimationOver = true;
			}
		}
	}
}

void Door::setOpening()
{
	this->isOpening = true;
	this->isTransparent = true;
	if (isSecretPassage) this->currentTextureCoordinates.y += 1;
}
