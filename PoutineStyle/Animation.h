#pragma once
#include "SFML/Graphics.hpp"
class Animation
{
public:
	Animation() {}
	Animation(int x, int y, int width, int height, int frameCount, std::string texturePath);

	int ApplyToSprite(sf::Sprite& sprite)
	{
		sprite.setTexture(texture);
		sprite.setTextureRect(frames[currentRenderedFrameNum]);
		return currentRenderedFrameNum;
	}

	void update(float dt)
	{
		isAnimationOver = false;
		time += dt;
		while (time >= frameDuration)
		{
			time -= frameDuration;
			advance();
		}
	}
	bool isAnimationOver = true;
private:
	void advance()
	{
		if (++currentRenderedFrameNum >= nbFrames) {
			currentRenderedFrameNum = 0;
			isAnimationOver = true;
		}
	}

	int nbFrames = 4;
	int currentRenderedFrameNum = 0;
	sf::Texture texture;
	sf::IntRect* frames;
	float frameDuration = 0.1f;
	float time = 0;
};

