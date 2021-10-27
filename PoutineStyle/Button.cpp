#include "Button.h"
#include <iostream>
Button::Button() {
	/*this->position = sf::Vector2i(0, 0);
	this->width = 200;
	this->height = 100;
	this->color = sf::Color::Blue;
	this->text = "Default button";
	this->window = NULL;*/
}
Button::Button(sf::Vector2i pos, int width, int height, sf::Color color, std::wstring text, sf::RenderWindow* window) {
	this->position = pos;
	this->width = width;
	this->height = height;
	this->color = color;
	this->text = text;
	this->window = window;

	// Creating button
	topBorder = sf::RectangleShape(sf::Vector2f(width, 5));
	topBorder.setPosition(sf::Vector2f(this->position.x, this->position.y));
	topBorder.setFillColor(this->color);
	bottomBorder = sf::RectangleShape(sf::Vector2f(width, 5));
	bottomBorder.setPosition(sf::Vector2f(this->position.x, this->position.y + height));
	bottomBorder.setFillColor(this->color);
	leftBorder = sf::RectangleShape(sf::Vector2f(5, height));
	leftBorder.setPosition(sf::Vector2f(this->position.x, this->position.y));
	leftBorder.setFillColor(this->color);
	rightBorder = sf::RectangleShape(sf::Vector2f(5, height + 5));
	rightBorder.setPosition(sf::Vector2f(this->position.x + width, this->position.y));
	rightBorder.setFillColor(this->color);

	// Set background properties
	background = sf::RectangleShape(sf::Vector2f(width, height));
	sf::Color colorT;
	if (isHovering()) colorT = sf::Color(color.r, color.g, color.b, 190);
	else colorT = sf::Color(color.r, color.g, color.b, 128);
	background.setPosition(sf::Vector2f(position.x, position.y));
	background.setFillColor(colorT);

	// Text font
	font = sf::Font();
	font.loadFromFile("CollegiateBlackFLF.ttf");

}
void Button::draw() {
	// Button text
	sfText = sf::Text();
	sfText.setFont(font);
	sfText.setString(this->text);
	sfText.setFillColor(sf::Color::White);
	sfText.setCharacterSize(30);
	sfText.setPosition(this->position.x + width / 2 - (sfText.getCharacterSize() / 2) * (text.length() / 2) - 10, this->position.y + height / 2 - sfText.getCharacterSize() / 2);

	// Drawing everything on window
	this->window->draw(background);
	this->window->draw(topBorder);
	this->window->draw(bottomBorder);
	this->window->draw(leftBorder);
	this->window->draw(rightBorder);
	this->window->draw(sfText);
}
bool Button::isClicked() {
	if (this->isHovering()) {
		return sf::Mouse::isButtonPressed(sf::Mouse::Left);
	}
	else {
		return false;
	}
}

bool Button::isHovering() {
	sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	// Check horizontal
	if (mousePos.y >= position.y && mousePos.y <= position.y + height) {
		// check vertical
		if (mousePos.x >= position.x && mousePos.x <= position.x + width) {
			return true;
		}
		else return false;
	}
	else return false;
}