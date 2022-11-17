#include <SFML/Graphics.hpp>

#pragma once

class Card {
public:
	Card();
	Card(sf::Texture texture, int posX, int posY, bool isHide, int number);
	sf::Texture& getTexture();
	sf::Sprite& getSprite();

	int getNumber();
	bool isHide();
	bool isDeleted();
	void putDelet();
	void setHide(bool hide);
	void undoDelete();

private:
	sf::Texture texture;
	sf::Sprite sprite;

	bool deleted;
	bool hide;
	int number;
};

