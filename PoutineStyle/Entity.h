#pragma once
#include "SFML/Graphics.hpp"
#include "Player.h"
class Entity
{
protected:
	int HP = 1;
	float distUntilPlay = 0;
	bool toRemove = false;
public:
	Entity(int HP, sf::Vector2f mapPos);
	virtual void draw(sf::RenderTarget& target, Player player, double* ZBuffer, int viewWidth, int viewHeight) = 0;
	virtual void update(float dt) = 0;
	sf::Vector2f mapPos;
	void setDistanceFromPlayer(float dist) { distUntilPlay = dist; }
	void calculateDistanceUntilPlayer(Player player) {
		distUntilPlay = ((player.position.x - this->mapPos.x) * (player.position.x - this->mapPos.x) + (player.position.y - this->mapPos.y) * (player.position.y - this->mapPos.y));
	}
	float getDistance() { return this->distUntilPlay; }
	int getHP() { return this->HP; }
	void decreaseHP(int damage) { this->HP -= damage; }
	void setToRemove(bool b) { this->toRemove = b; }
	bool getToRemove() { return this->toRemove; }
};