#include "Portal.h"
Portal::Portal(sf::Vector2f pos) : Entity(1, pos) {

}
Portal::~Portal()
{
	delete this->PortalAnimVA; this->PortalAnimVA = nullptr;
}
void Portal::draw(sf::RenderTarget& target, sf::Vector2f playerPos, sf::Vector2f playerDir, sf::Vector2f playerPlaneVec, double* ZBuffer, int viewWidth, int viewHeight) {
	if(this->toDraw) this->PortalAnimVA->draw(target, this->mapPos, playerPos, playerDir, playerPlaneVec, ZBuffer, viewWidth, viewHeight);

}
void Portal::update(float dt) {
	if (this->toDraw) this->PortalAnimVA->update(dt);
}