#include "Player.h"
#include "Bullet.h"
Player::Player() {
	this->knife = new Knife();
	this->currentWeapon = this->knife;
	this->secondaryWeapon = nullptr;
}

void Player::draw(sf::RenderTarget& target) const {
	currentWeapon->draw(target);
}

void Player::update(float dt) {
	currentWeapon->update(dt);
}

std::stack<Bullet*> Player::shoot(sf::Vector2f direction){
	std::stack<Bullet*> bullets;
	if (Player::currentAmmunition > 0)
	{
		bullets = currentWeapon->shoot(direction, this->position);
		currentAmmunition -= bullets.size();
		return bullets;
	}
	return bullets;
}

void Player::switchWeapon()
{
	if (this->secondaryWeapon != nullptr && this->secondaryWeapon != this->currentWeapon) {
		this->currentWeapon = this->secondaryWeapon;
	}
	else {
		if (this->currentWeapon != this->knife) this->secondaryWeapon = this->currentWeapon;
		this->currentWeapon = this->knife;
	}
}

void Player::reload()
{
	if (ammunition > 0)
	{
		// Reload animation
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
