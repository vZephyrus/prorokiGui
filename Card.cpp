#include "Card.h"
#include <iostream>

using namespace std;

Card::Card(sf::Texture texture, int posX, int posY, bool isHide, int number) {
	this->texture = texture;
	this->number = number;
	
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition(sf::Vector2f(posX, posY));

	this->hide = isHide;

}

Card::Card() {}

sf::Texture& Card::getTexture() {
	return texture;
}
sf::Sprite& Card::getSprite() {
	return sprite;
}
bool Card::isHide() {
	return hide;
}
int Card::getNumber() {
	return this->number;
}
bool Card::isDeleted() {
	return deleted;
}
void Card::putDelet() {
	this->deleted = true;
}

void Card::setHide(bool hide) {
	this->hide = hide;
}
void Card::undoDelete() {
	this->deleted = false;
}