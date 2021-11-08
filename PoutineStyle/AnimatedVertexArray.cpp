#include "AnimatedVertexArray.h"
sf::VertexArray AnimatedVertexArray::vertStripesArray = sf::VertexArray(sf::Lines, 2 * 1000);
AnimatedVertexArray::AnimatedVertexArray(std::string texturesPath, int spriteHeight, int spriteWidth, int y, int totalFrame) {
    this->textures = sf::Texture();
    this->textures.loadFromFile(texturesPath);
	this->spriteHeight = spriteHeight;
    this->spriteWidth = spriteWidth;
    this->y = y;
	this->nbFrames = totalFrame;
}
void AnimatedVertexArray::draw(sf::RenderTarget& target, sf::Vector2f entityMapPos, Player player, double* ZBuffer) {
    int yOffset = 100;
    // Raycast the entity
    int w = target.getSize().x;
    // Translate sprite pos relative to the camera
    double spriteX = (double)entityMapPos.x - player.position.x / 32;
    //spriteX += 0.5; // Center the sprite in the cell
    double spriteY = (double)entityMapPos.y - player.position.y / 32;
    //spriteY += 0.5; // Center the sprite in the cell

    // Projection values
    double invDet = 1.0 / ((double)player.planeVec.x * (double)player.direction.y - (double)player.direction.x * (double)player.planeVec.y);

    double transformX = invDet * (player.direction.y * spriteX - player.direction.x * spriteY);
    double transformY = invDet * (-player.planeVec.y * spriteX + player.planeVec.x * spriteY);

    if (transformY > 0) {

        int spriteScreenX = floor((w / 2.0) * (1.0 + transformX / transformY));
        int h = target.getSize().y;
        int spriteHeightOnScreen = abs(floor(h / transformY));

        // Where the sprite should be displayed (on screen y coordinates)
        int drawStartY = -spriteHeightOnScreen / 2 + h / 2;
        int drawEndY = spriteHeightOnScreen / 2 + h / 2;

        //calculate width of the sprite
        int spriteWidthOnScreen = abs(floor(h / (transformY)));

        // Where the sprite should be displayed (on screen x coordinates)
        int drawStartX = -spriteWidthOnScreen / 2 + spriteScreenX;
        if (drawStartX < 0) drawStartX = 0;
        int drawEndX = spriteWidthOnScreen / 2 + spriteScreenX;
        if (drawEndX >= w) drawEndX = w - 1;

        for (int j = drawStartX; j < drawEndX; j++) {
            // X coordinates of the sprite on the texture (y is useless, because it's always 0)
            int texX = int(256 * (j - (-spriteWidthOnScreen / 2 + spriteScreenX)) * spriteWidth / spriteWidthOnScreen) / 256;

            if (transformY > 0 && transformY < ZBuffer[j] && j > 0 && j < w) { // Draw it only there isn't a wall in front of it, if it's on screen and not behind the player
                vertStripesArray[j * 2].position = sf::Vector2f((float)j, (float)drawStartY + yOffset);
                vertStripesArray[j * 2].color = sf::Color::White;
                vertStripesArray[j * 2].texCoords = sf::Vector2f((float)texX + currentRenderedFrameNum * spriteWidth, (float)(spriteHeight * this->y));

                vertStripesArray[j * 2 + 1].position = sf::Vector2f((float)j, (float)drawEndY + yOffset);
                vertStripesArray[j * 2 + 1].color = sf::Color::White;
                vertStripesArray[j * 2 + 1].texCoords = sf::Vector2f((float)texX + currentRenderedFrameNum * spriteWidth, (float)(spriteHeight * this->y + spriteHeight - 1));
                isDrawn = true;
            }
        }

        if (isDrawn) {
            target.draw(vertStripesArray, &this->textures);
            this->vertStripesArray.clear(); // Clear the VertexArray only if something was drawn on screen to prevent performance issue
            this->vertStripesArray.resize(2 * w); // Resize 
        }
        isDrawn = false;
    }
}
void AnimatedVertexArray::update(float dt) {
	// Update the currentRenderedFrameNum depending on the deltaTime
	time += dt;
	while (time >= frameDuration) {
		time -= frameDuration;
		if (++currentRenderedFrameNum >= nbFrames) currentRenderedFrameNum = 0;
	}
}