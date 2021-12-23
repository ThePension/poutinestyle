#pragma once
#include "SFML/Graphics.hpp"

class Entity
{
protected:
	int HP = 1;
	float distUntilPlay = 0;
	bool toRemove = false;
	bool toDraw = false;
	bool isDestructible = false;
public:
	Entity(int HP, sf::Vector2f mapPos, bool isDestrutible = false);
	virtual ~Entity() = 0;
	virtual void draw(sf::RenderTarget& target, sf::Vector2f playerPos, sf::Vector2f playerDir, sf::Vector2f playerPlaneVec, double* ZBuffer, int viewWidth, int viewHeight) = 0;
	virtual void update(float dt) = 0;
	sf::Vector2f mapPos;
	void setDistanceFromPlayer(float dist) { distUntilPlay = dist; }
	void calculateDistanceUntilPlayer(sf::Vector2f playerPos) {
		distUntilPlay = ((playerPos.x - this->mapPos.x) * (playerPos.x - this->mapPos.x) + (playerPos.y - this->mapPos.y) * (playerPos.y - this->mapPos.y));
	}
	float getDistance() { return this->distUntilPlay; }
	int getHP() { return this->HP; }
	void decreaseHP(int damage) { this->HP -= damage; }
	void setToRemove(bool b) { this->toRemove = b; }
	bool getToRemove() { return this->toRemove; }
	void setToDraw(bool toDraw) { this->toDraw = toDraw; }
	bool getToDraw() { return this->toDraw; }
	bool getIsDestructible() { return this->isDestructible; }
	static bool isDoor(char entitChar);
	static bool isWall(char entityChar);
};