#pragma once
#include "Wall.h"
class Door : public Wall
{
public:
	Door(sf::Vector2f pos, int frameCount, int y, double frameDuration, bool isDestructible = false, bool isSecretPassage = false);
	~Door();
	void update(float dt) override;
	bool getIsOpening() { return this->isOpening; }
	bool getIsSecretPassage() { return this->isSecretPassage; }
	void setOpening();
private:
	bool isOpening = false;
	bool isSecretPassage = false;
};

