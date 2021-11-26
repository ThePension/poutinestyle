#include "Portal.h"
Portal::Portal(int hp, sf::Vector2f pos) : Entity(hp, pos) {

}
void Portal::draw(sf::RenderTarget& target, Player player, double* ZBuffer, int viewWidth, int viewHeight) {
	if(this->toDraw) this->PortalAnimVA.draw(target, this->mapPos, player, ZBuffer, viewWidth, viewHeight);

}
void Portal::update(float dt) {
	if (this->toDraw) this->PortalAnimVA.update(dt);
}