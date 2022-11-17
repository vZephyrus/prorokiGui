#include "Card.h"

#pragma once

struct Point {
	float x;
	float y;
};

class AnimationCard {
public:
	AnimationCard();
	AnimationCard(Point point, sf::Texture* emptyCardWhite, sf::Texture* emptyCardBlack);

	void copyCardToAnim(Card copyCardToAnim, bool hideCard);
	void setPoint(Point point);
	void animation(sf::RenderWindow& render);
	void update(sf::RenderWindow& render);
	void removeCard();

	Card* getCardToAnim();
	Point getToCard();
	bool isCardOnSide();

private:
	Point point;
	Card* cardToAnim;
	float speedY = 0;
	const float SPEED_ANIM = 20;
	bool cardOnSide = false;
	sf::Texture *emptyCardWhite, *emptyCardBlack;
};

