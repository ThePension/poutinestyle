#pragma once
#include "SFML/Graphics.hpp"
#include "Player.h"
class Entity
{
protected:
	int HP = 1;
	bool isVisible = false;
	float distUntilPlay = 0;
public:
	virtual void draw(sf::RenderTarget& target, Player player, double* ZBuffer) = 0;
	virtual void update(float dt) = 0;
	sf::Vector2f mapPos;
	bool getIsVisible() { return isVisible; }
	void setIsVisible(bool b) { isVisible = b; }
	void setDistanceFromPlayer(float dist) { distUntilPlay = dist; }
	void calculateDistanceUntilPlayer(Player player) {
		distUntilPlay = ((player.position.x/32 - this->mapPos.x) * (player.position.x / 32 - this->mapPos.x) + (player.position.y / 32 - this->mapPos.y) * (player.position.y / 32 - this->mapPos.y));
	}
	float getDistance() { return this->distUntilPlay; }
};