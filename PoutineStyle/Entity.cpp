#include "Entity.h"

Entity::Entity(int HP, sf::Vector2f mapPos)
{
	this->HP = HP;
	this->mapPos = mapPos;
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
            entityChar == 'a' ||
            entityChar == 'A' ||
            entityChar == 'b' ||
            entityChar == 'c' ||
            entityChar == 'C' ||
            entityChar == 'd' ||
            entityChar == 'D' ||
            entityChar == 'e' ||
            entityChar == 'E' ||
            entityChar == 'f' ||
            entityChar == 'F' ||
            entityChar == 'g' ||
            entityChar == 'G' ||
            entityChar == 'h' ||
            entityChar == 'H' ||
            entityChar == 'i' ||
            entityChar == 'I' ||
            entityChar == 'j' ||
            entityChar == 'J' ||
            entityChar == 'k' ||
            entityChar == 'K' ||
            entityChar == 'l' ||
            entityChar == 'V' ||
            entityChar == 'W' ||
            entityChar == 'X' ||
            entityChar == 'Y' ||
            entityChar == 'Z';
    }
