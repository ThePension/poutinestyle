#pragma once
#include "SFML/Graphics.hpp"
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
	bool isAnimationOver = false;

	float frameDuration = 0.1f;
	float time = 0;

	sf::VertexArray* vertStripesArray = new sf::VertexArray(sf::Lines, 0);
public:
	AnimatedVertexArray();
	AnimatedVertexArray(std::string texturesPath, int spriteHeight, int spriteWidth, int y, int totalFrame, double holdTime = 0.1);
	~AnimatedVertexArray();
	void draw(sf::RenderTarget& target, sf::Vector2f entityMapPos, sf::Vector2f playerPos, sf::Vector2f playerDir, sf::Vector2f playerPlaneVec, double* ZBuffer, int viewWidth, int viewHeight); // Draw the VertexArray on screen (do the raycast)
	void update(float dt); // Anime the VertexArray
	static double map(double value, double start1, double stop1, double start2, double stop2) {
		return start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1));
	}
	void resetAnimation() { this->currentRenderedFrameNum = 0; time = 0; }
	bool getIsAnimationOver() { return this->isAnimationOver; }
	int getCurrentRenderedFrameNum() { return this->currentRenderedFrameNum; }
};