#include "Entity.h"

Entity::Entity(int HP, sf::Vector2f mapPos, bool isDestructible)
{
    
	this->HP = HP;
	this->mapPos = mapPos;
    this->isDestructible = isDestructible;
}

Entity::~Entity() {

}

bool Entity::isDoor(char entityChar)
{
    return  entityChar == 'D' ||
            entityChar == 'V' ||
            entityChar == 'W' ||
            entityChar == 'X' ||
            entityChar == 'Y' ||
            entityChar == 'Z';
}

bool Entity::isWall(char entityChar)
{
    return  entityChar == '1' ||
            entityChar == '2' ||
            entityChar == '3' ||
            entityChar == '4' ||
            entityChar == '5' ||
            entityChar == '6' ||
            entityChar == '7' ||
            entityChar == '8' ||
            entityChar == '9' ||
            entityChar == 'D' ||
            entityChar == 'V' ||
            entityChar == 'W' ||
            entityChar == 'X' ||
            entityChar == 'Y' ||
            entityChar == 'Z';
}
