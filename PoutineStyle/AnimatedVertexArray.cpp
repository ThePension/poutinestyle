#include "AnimatedVertexArray.h"
sf::VertexArray AnimatedVertexArray::vertStripesArray = sf::VertexArray(sf::Lines, 0);
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
    double w = target.getSize().x * 1.0;
    // Translate sprite pos relative to the camera
    double spriteX = (double)entityMapPos.x - (double)player.position.x / 32.0;
    spriteX += map(entityMapPos.x, 0, 32, 0.5, -0.5); // Center the sprite in the cell
    double spriteY = (double)entityMapPos.y - (double)player.position.y / 32.0;
    spriteY += map(entityMapPos.y, 0, 32, 0.5, -0.5); // Center the sprite in the cell

    // Projection values
    double invDet = 1.0 / ((double)player.planeVec.x * (double)player.direction.y - (double)player.direction.x * (double)player.planeVec.y);

    double transformX = invDet * ((double)player.direction.y * spriteX - (double)player.direction.x * spriteY);
    double transformY = invDet * (-(double)player.planeVec.y * spriteX + (double)player.planeVec.x * spriteY);

    if (transformY > 0) {
        double spriteScreenX = floor((w / 2.0) * (1.0 + transformX / transformY));
        double h = target.getSize().y * 1.0;
        double spriteHeightOnScreen = abs(floor(h / transformY));

        // Where the sprite should be displayed (on screen y coordinates)
        double drawStartY = -spriteHeightOnScreen / 2.0 + h / 2.0;
        double drawEndY = spriteHeightOnScreen / 2.0 + h / 2.0;

        //calculate width of the sprite
        double spriteWidthOnScreen = abs(floor(h / (transformY)));

        // Where the sprite should be displayed (on screen x coordinates)
        double drawStartX = -spriteWidthOnScreen / 2.0 + spriteScreenX;
        if (drawStartX < 0) drawStartX = 0;
        double drawEndX = spriteWidthOnScreen / 2.0 + spriteScreenX;
        if (drawEndX >= w) drawEndX = w - 1.0;

        for (int j = drawStartX; j < drawEndX; j++) {
            // X coordinates of the sprite on the texture (y is useless, because it's always 0)
            int texX = int(256 * (j - (-spriteWidthOnScreen / 2 + spriteScreenX)) * spriteWidth / spriteWidthOnScreen) / 256;

            if (transformY > 0 && transformY < ZBuffer[j] && j > 0 && j < w) { // Draw it only there isn't a wall in front of it, if it's on screen and not behind the player
                sf::Vertex topVertex = sf::Vertex();
                topVertex.position = sf::Vector2f((float)j, (float)drawStartY + yOffset);
                topVertex.color = sf::Color::White;
                topVertex.texCoords = sf::Vector2f((float)texX + currentRenderedFrameNum * spriteWidth, (float)(spriteHeight * this->y));

                vertStripesArray.append(topVertex);

                sf::Vertex bottomVertex = sf::Vertex();
                bottomVertex.position = sf::Vector2f((float)j, (float)drawEndY + yOffset);
                bottomVertex.color = sf::Color::White;
                bottomVertex.texCoords = sf::Vector2f((float)texX + currentRenderedFrameNum * spriteWidth, (float)(spriteHeight * this->y + spriteHeight - 1));
                
                vertStripesArray.append(bottomVertex);

                isDrawn = true;
            }
        }

        if (isDrawn) {
            target.draw(vertStripesArray, &this->textures);
            this->vertStripesArray.clear(); // Clear the VertexArray only if something was drawn on screen to prevent performance issue            
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