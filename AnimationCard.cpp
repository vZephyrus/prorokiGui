#include "AnimationCard.h"
#include <iostream>
AnimationCard::AnimationCard() {  }

AnimationCard::AnimationCard(Point point, sf::Texture* emptyCardWhite, sf::Texture* emptyCardBlack) {
	this->point = point;
	this->emptyCardWhite = emptyCardWhite;
	this->emptyCardBlack = emptyCardBlack;

}

void AnimationCard::copyCardToAnim(Card copyCardToAnim, bool hideCard) {
	if (this->cardToAnim == nullptr) { 
		delete cardToAnim; 
		std::cout << "usunieto" << std::endl;
	}

	this->cardToAnim = new Card(copyCardToAnim.getTexture(), copyCardToAnim.getSprite().getPosition().x, copyCardToAnim.getSprite().getPosition().y, hideCard, copyCardToAnim.getNumber());
	if (hideCard) {
		int nmb = this->cardToAnim->getNumber();
		if (nmb == 1 || nmb == 3 || nmb == 5 || nmb == 7) {
			this->cardToAnim->getSprite().setTexture(*emptyCardWhite);
		}
		else {
			this->cardToAnim->getSprite().setTexture(*emptyCardBlack);
		}
		
	}


	float odleglosc_width = point.x - cardToAnim->getSprite().getPosition().x;
	float odleglosc_height = point.y - cardToAnim->getSprite().getPosition().y;
	speedY = odleglosc_height / odleglosc_width * SPEED_ANIM;
	cardOnSide = false;
}
void AnimationCard::setPoint(Point point) {
	this->point = point;
}

void AnimationCard::animation(sf::RenderWindow& render) {
	render.draw(cardToAnim->getSprite());
}

void AnimationCard::update(sf::RenderWindow& render) {
	if (cardToAnim == nullptr) { 
		return; 
	}

	sf::Sprite* spr = &cardToAnim->getSprite();

	int x = spr->getPosition().x;
	int y = spr->getPosition().y;

	if (x+SPEED_ANIM < point.x) {		
		spr->setPosition(sf::Vector2f(spr->getPosition().x + SPEED_ANIM, spr->getPosition().y + speedY));
	}
	else {
		spr->setPosition(sf::Vector2f(point.x, point.y)); 
		cardOnSide = true;
	}
}
void AnimationCard::removeCard() {
	if (cardToAnim != nullptr) {
		int num = cardToAnim->getNumber();
		cardToAnim = nullptr;
		delete cardToAnim;
		std::cout << " Usunieto karte :" << num << std::endl;
	}
}

Card* AnimationCard::getCardToAnim() {
	return this->cardToAnim;
}
Point AnimationCard::getToCard() {
	return this->point;
}

bool AnimationCard::isCardOnSide() {
	return this->cardOnSide;
}