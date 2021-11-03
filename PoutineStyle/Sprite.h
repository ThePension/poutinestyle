#pragma once
struct Sprite {
	char type;
	double distance;
	int mapX, mapY;
};
// Used for sorting vector of sprites
bool compareSpriteDistance(Sprite s1, Sprite s2)
{
	return (s1.distance > s2.distance);
}
