#include "Player.h"
#include "Bullet.h"

Player::Player() {
	this->knife = new Knife();
	this->currentWeapon = this->knife;
	this->secondaryWeapon = nullptr;
}

Player::~Player()
{
	delete knife; knife = nullptr;
	// Keys and other Weapons are deleted in StatePlayGame
}

Player::Player(int live, int ammunition) : Player()
{
	this->live = 1;
	this->nbChargers = 0;
	this->ammunition = ammunition;
	this->currentAmmunition = 0;
}

Weapon* Player::setWeapon(Weapon* w) {
	Weapon* oldWeapon = this->secondaryWeapon;

	if (typeid(*w).name() == typeid(Pistol).name())
	{
		this->currentAmmunition = 12;
		this->chargerCapacity = 12;
		this->ammunition = this->nbChargers * 12;
	}
	else if (typeid(*w).name() == typeid(Shotgun).name())
	{
		this->currentAmmunition = 2;
		this->chargerCapacity = 2;
		this->ammunition = this->nbChargers * 2;
	}
	else if (typeid(*w).name() == typeid(Uzi).name())
	{
		this->currentAmmunition = 30;
		this->chargerCapacity = 30;
		this->ammunition = this->nbChargers * 30;
	}
	else if (typeid(*w).name() == typeid(GrenadeLauncher).name())
	{
		this->currentAmmunition = 1;
		this->chargerCapacity = 1;
		this->ammunition = this->nbChargers;
	}

	this->secondaryWeapon = w;
	this->currentWeapon = w;
	return oldWeapon;
}

void Player::draw(sf::RenderTarget& target) const {
	// Draw weapon
	currentWeapon->draw(target);

	// Draw possessed keys
	int count = 0;
	for (Key* key : playerKeys) {
		sf::Sprite keySprite = key->getFirstSprite();
		// Scale the sprite
		double wantedSpriteSize = target.getSize().x / 25.0;
		double ratio = wantedSpriteSize / keySprite.getTextureRect().width;
		keySprite.scale(sf::Vector2f(ratio, ratio));

		// Set position
		keySprite.setPosition(target.getSize().x / 2 - wantedSpriteSize - 10, count * wantedSpriteSize + 30);

		target.draw(keySprite);

		count++;
	}
}

void Player::update(float dt) {
	currentWeapon->update(dt);
}

std::stack<Bullet*> Player::shoot(sf::Vector2f direction){
	std::stack<Bullet*> bullets;
	if (Player::currentAmmunition > 0 || typeid(*this->currentWeapon).name() == typeid(Knife).name())
	{
		bullets = currentWeapon->shoot(direction, this->position);
		currentAmmunition -= bullets.size();
		return bullets;
	}
	return bullets;
}

std::stack<Bullet*> Player::burstShooting(sf::Vector2f direction) {
	std::stack<Bullet*> bullets;
	if (Player::currentAmmunition > 0)
	{
		bullets = dynamic_cast <Uzi*>(currentWeapon)->burstShooting (direction, this->position);
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

void Player::clearKeys()
{
	this->playerKeys.clear();
}

void Player::reload()
{
	if (ammunition > 0)
	{		
		nbChargers--;

		if (ammunition >= this->chargerCapacity)
		{
			currentAmmunition = this->chargerCapacity;
			ammunition -= this->chargerCapacity;
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
	this->ammunition += this->chargerCapacity;
	this->nbChargers++;
}