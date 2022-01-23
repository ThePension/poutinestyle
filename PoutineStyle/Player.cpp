#include "Player.h"
#include "Bullet.h"

Player::Player() {
	this->knife = new Knife();
	this->currentWeapon = this->knife;
	this->secondaryWeapon = nullptr;

	// Sound
	knifeBuffer.loadFromFile("Ressource/Sound/PlayerKnife.wav");
	emptyGunBuffer.loadFromFile("Ressource/Sound/EmptyGun.wav");
	gunShotBuffer.loadFromFile("Ressource/Sound/PlayerGunShot.wav");
	shotgunShotBuffer.loadFromFile("Ressource/Sound/PlayerShotgun.wav");
	uziShotBuffer.loadFromFile("Ressource/Sound/PlayerUziShot.wav");
	grenadLauncherBuffer.loadFromFile("Ressource/Sound/PlayerGrenadLauncher.wav");
	gunReloadBuffer.loadFromFile("Ressource/Sound/ReloadGun.wav");
	shotgunReloadBuffer.loadFromFile("Ressource/Sound/ReloadShotgun.wav");
	uziReloadBuffer.loadFromFile("Ressource/Sound/ReloadUzi.wav");
	grenadeLauncherReloadBuffer.loadFromFile("Ressource/Sound/ReloadGrenadLauncher.wav");
	knifeSound.setBuffer(knifeBuffer);
	emptyGun.setBuffer(emptyGunBuffer);
	gunShot.setBuffer(gunShotBuffer);
	shotgunShot.setBuffer(shotgunShotBuffer);
	uziShot.setBuffer(uziShotBuffer);
	grenadLauncher.setBuffer(grenadLauncherBuffer);
	gunReload.setBuffer(gunReloadBuffer);
	shotgunReload.setBuffer(shotgunReloadBuffer);
	uziReload.setBuffer(uziReloadBuffer);
	grenadeLauncherReload.setBuffer(grenadeLauncherReloadBuffer);
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
		double wantedSpriteSize = target.getSize().x / 2.5;
		double ratio = wantedSpriteSize / keySprite.getTextureRect().width;
		keySprite.scale(sf::Vector2f(ratio, ratio));

		// Set position
		keySprite.setPosition(target.getSize().x - wantedSpriteSize + 80, count * wantedSpriteSize / 2.0 - wantedSpriteSize / 2.0);

		target.draw(keySprite);

		count++;
	}
}

void Player::update(float dt) {
	currentWeapon->update(dt);
}

std::stack<Bullet*> Player::shoot(sf::Vector2f direction){
	std::stack<Bullet*> bullets;
	if (Player::currentAmmunition == 0 && typeid(*this->currentWeapon).name() != typeid(Knife).name())
	{
		emptyGun.play();
	}
	else if (Player::currentAmmunition > 0 && typeid(*this->currentWeapon).name() == typeid(Pistol).name())
	{
		bullets = currentWeapon->shoot(direction, this->position);
		currentAmmunition -= bullets.size();
		gunShot.play();
		return bullets;
	}
	else if (Player::currentAmmunition > 0 && typeid(*this->currentWeapon).name() == typeid(Shotgun).name())
	{
		bullets = currentWeapon->shoot(direction, this->position);
		currentAmmunition -= bullets.size();
		shotgunShot.play();
		return bullets;
	}
	else if (Player::currentAmmunition > 0 && typeid(*this->currentWeapon).name() == typeid(Uzi).name())
	{
		bullets = currentWeapon->shoot(direction, this->position);
		currentAmmunition -= bullets.size();
		uziShot.play();
		return bullets;
	}
	else if (Player::currentAmmunition > 0 && typeid(*this->currentWeapon).name() == typeid(GrenadeLauncher).name())
	{
		bullets = currentWeapon->shoot(direction, this->position);
		currentAmmunition -= bullets.size();
		grenadLauncher.play();
		return bullets;
	}
	else if (typeid(*this->currentWeapon).name() == typeid(Knife).name())
	{
		bullets = currentWeapon->shoot(direction, this->position);
		currentAmmunition -= bullets.size();
		knifeSound.play();
		return bullets;
	}
	return bullets;
}

std::stack<Bullet*> Player::burstShooting(sf::Vector2f direction) {
	std::stack<Bullet*> bullets;
	if (Player::currentAmmunition == 0 ) emptyGun.play();
	if (Player::currentAmmunition > 0)
	{
		bullets = dynamic_cast <Uzi*>(currentWeapon)->burstShooting (direction, this->position);
		currentAmmunition -= bullets.size();
		uziShot.play();
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
		
		if(typeid(*this->currentWeapon).name() == typeid(Pistol).name()) gunReload.play();
		else if (typeid(*this->currentWeapon).name() == typeid(Shotgun).name()) shotgunReload.play();
		else if (typeid(*this->currentWeapon).name() == typeid(Uzi).name()) uziReload.play();
		else if (typeid(*this->currentWeapon).name() == typeid(GrenadeLauncher).name()) grenadeLauncherReload.play();

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
		// debug mode
		// health -= 100;
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