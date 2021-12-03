#include "Animation.h"

Animation::Animation() { }

Animation::Animation(int x, int y, int width, int height, int frameCount, std::string texturePath, float holdTime) {
	texture.loadFromFile(texturePath);
	this->nbFrames = frameCount;
	this->frameDuration = holdTime;
	frames.resize(frameCount);
	for (int i = 0; i < nbFrames; i++) {
		this->frames[i] = sf::IntRect(x + i * width, y + i * 0, width, height);
	}
}

Animation::~Animation()
{

}

void Animation::update(float dt)
{
	isAnimationOver = false;
	time += dt;
	while (time >= frameDuration)
	{
		time -= frameDuration;
		advance();
	}
}

int Animation::ApplyToSprite(sf::Sprite& sprite)
{
	sprite.setTexture(texture);
	sprite.setTextureRect(frames[currentRenderedFrameNum]);
	return currentRenderedFrameNum;
}

void Animation::advance()
{
	if (++currentRenderedFrameNum >= nbFrames) {
		currentRenderedFrameNum = 0;
		isAnimationOver = true;
	}
}
