#pragma once
#include "SFML/Graphics.hpp"
class Button
{
private:
	sf::RenderWindow* window;
	sf::Vector2i position;
	int width, height;
	sf::Color color;
	std::wstring text;
	sf::RectangleShape topBorder, bottomBorder, leftBorder, rightBorder, background;
	sf::Text sfText;
	sf::Font font;
	bool pressed = false;
	bool isHovering();
public:
	Button();
	Button(sf::Vector2i pos, int width, int height, sf::Color color, std::wstring text, sf::RenderWindow *);
	void draw();
	bool isClicked();
	bool isReleased();
	void selected(bool state);
};

