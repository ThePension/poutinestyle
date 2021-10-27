#pragma once
#include "SFML/Graphics.hpp"
class Button
{
private:
	sf::RenderWindow* window;
	sf::Vector2i position;
	int width, height;
	sf::Color color;
	std::string text;
	bool isHovering();
public:
	Button(sf::Vector2i pos, int width, int height, sf::Color color, std::string text, sf::RenderWindow *);
	void draw();
	bool isClicked();

};

