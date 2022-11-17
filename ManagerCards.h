#include "Card.h"
#include "AnimationCard.h"
#include <Windows.h>
#include <random>
#include "AnimationCaption.h"
#include <vector>
#include "Caption.h"

#pragma once
using namespace std;

class ManagerCards{
public:
	ManagerCards(sf::RenderWindow* window);
	sf::Texture loadTextureFromResource(const wchar_t* name);

	Card** getCardsPlayer();
	Card** getCardsBots();

	sf::Texture& getBlackTextureCard();
	sf::Texture& getWhiteTextureCard();

	bool isCollision(sf::FloatRect rect, int posX, int posY);

	//Main methods draw all cards
	void draw(sf::RenderWindow& renderWindow);

	//Main updates
	void update(sf::RenderWindow& window);

	//Main click
	void click();
	void setScale(float scale);
	void moveBot();
	void checkStateGame();
	void rozpocznijGre();

private:
	Card* cards_player[9];
	Card* cards_bot[9];
	sf::RenderWindow* window;
	sf::Texture emptyCardWhite, emptyCardBlack, texDeleted;
	sf::Sprite emptySprite, deletedSprite;
	float scale = 1;
	AnimationCard* animPlayer, *animBot;
	AnimationCaption* caption_twojRuch, *caption_poswiataKarty;
	
	int random_mt19937(int min, int max);
	void rozlosujKarty(Card** cards);
	void setVisibleAllCards(Card** cards, bool isHide);
	void resetKart();
	std::vector<int> cards_bot_chosen;
	Caption *cap_napisA, *pkt_gracz, *pkt_bot;
	sf::RectangleShape rect;


	//Main sterowanie
	bool player_bot = false;
	bool first_moveBot = true;
	bool blockClickPlayer = false;
	bool block_moveCards = false;

	sf::Clock cl_coutDownMoveBot, cl_coutToEnd, cl_twoCardOnSide;
	

	int pointPlayer = 0;
	int pointBot = 0;
};

