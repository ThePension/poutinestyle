#include "Player.h"
#include "Bullet.h"
Player::Player() {
	this->knife = new Knife();
	this->currentWeapon = this->knife;
}
void Player::draw(sf::RenderTarget& target) const {
	currentWeapon->draw(target);
}
void Player::update(float dt) {
	currentWeapon->update(dt);
}
Bullet* Player::shoot(sf::Vector2f direction){
	if (Player::currentAmmunition > 0)
	{
		Bullet* bullet = currentWeapon->shoot(direction, this->position);
		if(bullet != nullptr) Player::currentAmmunition--;
		return bullet;
	}
	return nullptr;
}

void Player::switchWeapon()
{
	if (this->secondaryWeapon != this->currentWeapon && this->secondaryWeapon != nullptr) {
		this->currentWeapon = this->secondaryWeapon;
	}
	else {
		this->currentWeapon = this->knife;
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
