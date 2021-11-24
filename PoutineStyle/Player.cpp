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
void Player::shoot(std::list<Bullet*>& bullets, sf::Vector2f direction){
	loseLife();
	if (Player::currentAmmunition > 0)
	{
		if (weapon->getShootAnimation().isAnimationOver) {
			isShooting = true;

			// Add noise to the bullet direction
			double xNoise = (double)rand() / (RAND_MAX * 10.0); // Between 0 and 0.1
			double yNoise = (double)rand() / (RAND_MAX * 10.0); // Between 0 and 0.1
			sf::Vector2f directionWithNoise = sf::Vector2f(direction.x + xNoise, direction.y + yNoise);

			// Create a bullet
			sf::Vector2f bulletPos = sf::Vector2f(this->position.x - 0.5 + 2.0 * this->direction.x, this->position.y - 0.5 + 2.0 * this->direction.y);
			Bullet* bullet = new Bullet(1, bulletPos, directionWithNoise, true);
			bullets.push_back(bullet);

			// Decrement ammunition
			Player::currentAmmunition--;
			std::printf("qqch");
			int tamere = getCurrentAmmunition();
			std::cout << tamere << std::endl;
		}
	}
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
	}
	else
	{
		if (live > 0)
		{
			live -= 1;
			health = 100;
		}
		else
		{
			//mort
			std::cout << "tu es mort looser" << std::endl;
		}
	}

}
