#include "Ennemy.h"
#include <random>

Ennemy::Ennemy(int hp, sf::Vector2f pos, int dropNumber) : Entity(hp, pos) {
	srand(time(NULL)); // Randomize seed
        // Create random entity for drop
    switch (dropNumber)
    {
        case 0: // Ammo pack
            droppedEntity = new Ammo(1, this->mapPos);
            break;
        case 1: // Medikit
            droppedEntity = new Medikit(1, this->mapPos);
            break;
    }
}

void Ennemy::draw(sf::RenderTarget& target, Player player, double* ZBuffer, int viewWidth, int viewHeight) {
	if (isShooting) {
		this->shootAnimVA.draw(target, this->mapPos, player, ZBuffer, viewWidth, viewHeight);
	}
	else if(isWalking) { /* Do stuff */ }
    else if (isDying) {
        this->dieAnimVA.draw(target, this->mapPos, player, ZBuffer, viewWidth, viewHeight);
    }
	else {
		this->shootAnimVA.draw(target, this->mapPos, player, ZBuffer, viewWidth, viewHeight);
	}
}

void Ennemy::update(float dt) {
	if (isShooting) {
		this->shootAnimVA.update(dt);
		if (shootAnimVA.getIsAnimationOver()) {
			isShooting = false;
		}
    }
    else if (isDying) {
        this->dieAnimVA.update(dt);
        if (this->dieAnimVA.getIsAnimationOver()) {
            this->toRemove = true;
        }
    }
}

void Ennemy::shoot(std::list<Bullet*>& bullets, sf::Vector2f direction, sf::Vector2f playerPos, char** map) {
    bool bIsPlayerVisible = isPlayerVisible(playerPos, map);
	if (shootAnimVA.getIsAnimationOver() && bIsPlayerVisible) {
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
		bullets.push_back(bullet);
	}
}
bool Ennemy::isPlayerVisible(sf::Vector2f playerPos, char** map) {
    // Get the player position relative to the ennemy position
    double playerMapPosX = playerPos.x; // = (double)this->mapPos.x - (double)playerPos.x;
    double playerMapPosY = playerPos.y; // = (double)this->mapPos.y - (double)playerPos.y;

    // Cell where the entity is standing
    sf::Vector2i entityMapPos = sf::Vector2i(int(this->mapPos.x), int(this->mapPos.y));

    // Calculate the direction of the bullet (aiming the player)
    sf::Vector2f rayDir = sf::Vector2f(playerPos.x, playerPos.y) - this->mapPos;
    // Get the norm of the direction vector
    double norm = sqrt(pow(rayDir.x, 2) + pow(rayDir.y, 2));
    // Get the unit vector
    rayDir = sf::Vector2f(rayDir.x / norm, rayDir.y / norm);
    double deltaDistX = (rayDir.x == 0) ? 0 : abs(1 / rayDir.x); // RayDir is a unit vector, length = 1
    double deltaDistY = (rayDir.y == 0) ? 0 : abs(1 / rayDir.y);

    double sideDistX, sideDistY;

    int stepX, stepY;
    bool wallHit = false, isWallHitHorizontal = false;

    if (rayDir.x < 0) {
        stepX = -1;
        sideDistX = ((this->mapPos.x) - double(entityMapPos.x)) * deltaDistX;
    }
    else {
        stepX = 1;
        sideDistX = (double(entityMapPos.x) + 1.f - (this->mapPos.x)) * deltaDistX;
    }
    if (rayDir.y < 0) {
        stepY = -1;
        sideDistY = ((this->mapPos.y) - double(entityMapPos.y)) * deltaDistY;
    }
    else {
        stepY = 1;
        sideDistY = (double(entityMapPos.y) + 1.f - (this->mapPos.y)) * deltaDistY;
    }
    
    // DDA algorithm
    while (entityMapPos.x > 0 && entityMapPos.x < 32 && entityMapPos.y > 0 && entityMapPos.y < 32) {
        if (sideDistX < sideDistY) {
            sideDistX += deltaDistX; // Always the same
            entityMapPos.x += stepX;
            isWallHitHorizontal = true;
        }
        else {
            sideDistY += deltaDistY;
            entityMapPos.y += stepY;
            isWallHitHorizontal = false;
        }
        if (map[entityMapPos.y][entityMapPos.x] == '1' ||
            map[entityMapPos.y][entityMapPos.x] == 'D' ||
            map[entityMapPos.y][entityMapPos.x] == 'V' ||
            map[entityMapPos.y][entityMapPos.x] == 'W' ||
            map[entityMapPos.y][entityMapPos.x] == 'X' ||
            map[entityMapPos.y][entityMapPos.x] == 'Y' ||
            map[entityMapPos.y][entityMapPos.x] == 'Z') return false; // The player is not visible for the ennemy
        else if (entityMapPos.x == floor(playerPos.x) && entityMapPos.y == floor(playerPos.y)) return true; // The player is visible for the ennemy
    }
}