#include "Entity.h"

Entity::Entity(int HP, sf::Vector2f mapPos)
{
	this->HP = HP;
	this->mapPos = mapPos;
}

Entity::~Entity() {

}
