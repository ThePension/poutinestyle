#include "General.h"

General::General(sf::Vector2f pos, int dropNumber)
    : Ennemy(3, pos, AnimatedVertexArray("../PoutineStyle/pics/generalTextures.png", 64, 64, 1, 4, 0.1),
                     AnimatedVertexArray("../PoutineStyle/pics/generalTextures.png", 64, 64, 2, 4, 0.3), dropNumber) {

}

std::stack<Bullet*> General::shoot(sf::Vector2f direction, sf::Vector2f playerPos, char** map)
{
	bool bIsPlayerVisible = isPlayerVisible(playerPos, map);
	std::stack<Bullet*> bullets;
	if (shootAnimVA.getIsAnimationOver() && bIsPlayerVisible && !isDying) {
		isShooting = true;
		// Add noise to the bullet direction
		double xNoise = (double)rand() / (RAND_MAX * 10.0); // Between 0 and 0.1
		xNoise = AnimatedVertexArray::map(xNoise, 0, 0.1, -0.1, 0.1);
		double yNoise = (double)rand() / (RAND_MAX * 10.0); // Between 0 and 0.1
		yNoise = AnimatedVertexArray::map(yNoise, 0, 0.1, -0.1, 0.1);
		sf::Vector2f directionWithNoise = sf::Vector2f(direction.x + xNoise, direction.y + yNoise);

		// Create a bullet
		sf::Vector2f bulletPos1 = sf::Vector2f((this->mapPos.x), (this->mapPos.y));
		Bullet* bullet1 = new Bullet(1, bulletPos1, directionWithNoise, false);
		bullets.push(bullet1);
		return bullets;
	}
	return bullets;
}
