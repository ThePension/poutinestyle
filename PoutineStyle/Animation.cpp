#include "Animation.h"

Animation::Animation(int x, int y, int width, int height, std::string texturePath)
{
	texture.loadFromFile(texturePath);
	for (int i = 0; i < nbFrames; i++)
	{
		frames[i] = sf::IntRect(x + i * width, y + i * 0, width, height);
	}
}