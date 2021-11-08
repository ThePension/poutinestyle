#pragma once
#include "SFML/Graphics.hpp"
#include "Player.h"
#include <iostream>
class AnimatedVertexArray
{
private:
	sf::Texture textures;
	int spriteHeight = 64, spriteWidth = 64;
	int y = 0;
	int nbFrames = 4;
	int currentRenderedFrameNum = 0;
	bool isDrawn = false;

	float frameDuration = 0.1f;
	float time = 0;

	static sf::VertexArray vertStripesArray;
public:
	AnimatedVertexArray(std::string texturesPath, int spriteHeight, int spriteWidth, int y, int totalFrame);
	void draw(sf::RenderTarget& target, sf::Vector2f entityMapPos, Player player, double* ZBuffer); // Draw the VertexArray on screen (do the raycast)
	void update(float dt); // Anime the VertexArray
};