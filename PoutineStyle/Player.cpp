#include "Player.h"
#include "Bullet.h"
Player::Player() {
	this->weapon = new Weapon();
}
void Player::draw(sf::RenderTarget& target) const {
	weapon->draw(target);
}
void Player::update(float dt) {
	if (isShooting) {
		weapon->update(dt);
		if (weapon->getShootAnimation().isAnimationOver) isShooting = false;
	}	
}
Bullet* Player::shoot(sf::Vector2f direction){
	if (Player::currentAmmunition > 0)
	{
		if (weapon->getShootAnimation().isAnimationOver) {
			isShooting = true;

			// Add noise to the bullet direction
			double xNoise = (double)rand() / (RAND_MAX * 10.0); // Between 0 and 0.1
			xNoise = AnimatedVertexArray::map(xNoise, 0, 0.1, -0.1, 0.1);
			double yNoise = (double)rand() / (RAND_MAX * 10.0); // Between 0 and 0.1

			yNoise = AnimatedVertexArray::map(yNoise, 0, 0.1, -0.1, 0.1);
			sf::Vector2f directionWithNoise = sf::Vector2f(direction.x + xNoise/10, direction.y + yNoise/10);

			// Create a bullet
			sf::Vector2f bulletPos = sf::Vector2f(this->position.x - 0.5 + 2.0 * this->direction.x, this->position.y - 0.5 + 2.0 * this->direction.y);
			Bullet* bullet = new Bullet(1, bulletPos, directionWithNoise, true);

			// Decrement ammunition
			Player::currentAmmunition--;

			return bullet;
		}
	}
	return nullptr;
}

void Player::reload()
{
	if (ammunition > 0)
	{
		//Reload animation
		if (ammunition >= 7)
		{
			currentAmmunition = 7;
			ammunition -= 7;
		}
		else
		{
			currentAmmunition = ammunition;
			ammunition -= ammunition;
		}
	}
}

void Player::loseLife()
{
	if (health > 1)
	{
		health -= rand() % 6+1;
		//debug mode
		//health -= 100;
	}
	else
	{
		if (--live > 0) health = 100;
		else isDead = true;
	}
}

void Player::increaseLife()
{
	this->live++;
}

void Player::increaseAmmo()
{
	this->ammunition += 7;
}

bool Player::dead()
{
	return this->isDead;
}
