#pragma once
#include "SFML/Graphics.hpp"
class Animation
{
public:
	Animation();
	Animation(int x, int y, int width, int height, int frameCount, std::string texturePath, float holdTime = 0.1f);
	~Animation();
	int ApplyToSprite(sf::Sprite& sprite);
	void update(float dt);
	bool isAnimationOver = true;
	int getCurrentRenderedFramNum() { return this->currentRenderedFrameNum; }
private:
	void advance();
	int nbFrames = 4;
	int currentRenderedFrameNum = 0;
	sf::Texture texture;
	std::vector<sf::IntRect> frames;
	float frameDuration = 0.1f;
	float time = 0;
};

