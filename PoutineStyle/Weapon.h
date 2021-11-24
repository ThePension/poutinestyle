#pragma once
#include "Animation.h"
class Weapon
{
private:
	sf::Sprite weaponSprite = sf::Sprite();
	Animation shootAnimation = Animation(0, 0, 105, 105, "../PoutineStyle/pics/gunTexture.png");
	double shootCadendy = 1;
	int damage = 1;

public:
	Weapon();
	Weapon(double shootCadency, int damage, Animation shootAnim);
	void draw(sf::RenderTarget& target) const;
	void update(float dt);
	Animation getShootAnimation() { return this->shootAnimation; }
};