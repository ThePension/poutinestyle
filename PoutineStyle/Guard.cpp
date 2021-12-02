#include "Guard.h"

Guard::Guard(sf::Vector2f pos, int dropNumber)
    : Ennemy(1, pos, AnimatedVertexArray("../PoutineStyle/pics/shootingEnnemy.png", 64, 64, 0, 5, 0.3), 
		AnimatedVertexArray("../PoutineStyle/pics/dyingEnnemy.png", 64, 64, 0, 4, 0.3), dropNumber)
{
    
}

Bullet* Guard::shoot(sf::Vector2f direction, sf::Vector2f playerPos, char** map)
{
	bool bIsPlayerVisible = isPlayerVisible(playerPos, map);
	if (shootAnimVA.getIsAnimationOver() && bIsPlayerVisible && !isDying) {
		isShooting = true;
		// Add noise to the bullet direction
		double xNoise = (double)rand() / (RAND_MAX * 10.0); // Between 0 and 0.1
		xNoise = AnimatedVertexArray::map(xNoise, 0, 0.1, -0.1, 0.1);
		double yNoise = (double)rand() / (RAND_MAX * 10.0); // Between 0 and 0.1
		yNoise = AnimatedVertexArray::map(yNoise, 0, 0.1, -0.1, 0.1);
		sf::Vector2f directionWithNoise = sf::Vector2f(direction.x + xNoise, direction.y + yNoise);

		// Create a bullet
		sf::Vector2f bulletPos = sf::Vector2f((this->mapPos.x), (this->mapPos.y));
		Bullet* bullet = new Bullet(1, bulletPos, directionWithNoise, false);
		return bullet;
	}
	return nullptr;
}