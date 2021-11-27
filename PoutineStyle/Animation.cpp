#include "Animation.h"
Animation::Animation(int x, int y, int width, int height, int frameCount, std::string texturePath) {
	texture.loadFromFile(texturePath);
	this->nbFrames = frameCount;
	for (int i = 0; i < nbFrames; i++) {
		frames[i] = sf::IntRect(x + i * width, y + i * 0, width, height);
	}
}