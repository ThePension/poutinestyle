#pragma once
#include "SFML/Graphics.hpp"
class Animation
{
public:
	Animation(int x, int y, int width, int height, std::string texturePath);
	void ApplyToSprite(sf::Sprite & sprite) {
		sprite.setTexture(texture);
		sprite.setTextureRect(frames[currentRenderedFrameNum]);
	}
	void update(float dt) {
		time += dt;
		while (time >= frameDuration) {
			time -= frameDuration;
			advance();
		}
	}
private:
	void advance() {
		if (++currentRenderedFrameNum >= nbFrames) currentRenderedFrameNum = 0; 
	}
	static const int nbFrames = 4;
	int currentRenderedFrameNum = 0;
	sf::Texture texture;
	sf::IntRect frames[nbFrames];
	float frameDuration = 0.1f;
	float time = 0;
};

