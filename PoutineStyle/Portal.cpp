#include "Portal.h"
Portal::Portal(int hp, sf::Vector2f pos) : Entity(hp, pos) {

}
void Portal::draw(sf::RenderTarget& target, sf::Vector2f playerPos, sf::Vector2f playerDir, sf::Vector2f playerPlaneVec, double* ZBuffer, int viewWidth, int viewHeight) {
	if(this->toDraw) this->PortalAnimVA.draw(target, this->mapPos, playerPos, playerDir, playerPlaneVec, ZBuffer, viewWidth, viewHeight);

}
void Portal::update(float dt) {
	if (this->toDraw) this->PortalAnimVA.update(dt);
}