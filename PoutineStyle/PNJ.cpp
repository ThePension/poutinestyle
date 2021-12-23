#include "PNJ.h"
PNJ::PNJ(sf::Vector2f pos) : Entity(1, pos, false) {

}
PNJ::~PNJ()
{
	delete this->PortalAnimVA; this->PortalAnimVA = nullptr;
}
void PNJ::draw(sf::RenderTarget& target, sf::Vector2f playerPos, sf::Vector2f playerDir, sf::Vector2f playerPlaneVec, double* ZBuffer, int viewWidth, int viewHeight) {
	if(this->toDraw) this->PortalAnimVA->draw(target, this->mapPos, playerPos, playerDir, playerPlaneVec, ZBuffer, viewWidth, viewHeight);

}
void PNJ::update(float dt) {
	if (this->toDraw) this->PortalAnimVA->update(dt);
}