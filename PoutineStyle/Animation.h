#pragma once
#include "SFML/Graphics.hpp"
class Animation
{
	public:
		Animation(int x, int y, int width, int height, std::string texturePath);

		int ApplyToSprite(sf::Sprite& sprite)
		{
			sprite.setTexture(texture);
			sprite.setTextureRect(frames[currentRenderedFrameNum]);
			return currentRenderedFrameNum;
		}

		void update(float dt, bool shoot = true)
		{
			time += dt;
			while (time >= frameDuration)
			{
				time -= frameDuration;
				if (shoot)
				{
					advance();
				}
				else
				{
					currentRenderedFrameNum = 0;
				}
			}
		}

	private:
		void advance()
		{
			if (++currentRenderedFrameNum >= nbFrames) currentRenderedFrameNum = 0;
		}

		static const int nbFrames = 4;
		int currentRenderedFrameNum = 0;
		sf::Texture texture;
		sf::IntRect frames[nbFrames];
		float frameDuration = 0.1f;
		float time = 0;
};

