#include "Entity.h"

Entity::Entity(int HP, sf::Vector2f mapPos)
{
	this->HP = HP;
	this->mapPos = mapPos;
}

Entity::~Entity() {

}

bool Entity::isWall(Entity* entity)
{
	std::string entityType = typeid(*entity).name();
	return false;
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
