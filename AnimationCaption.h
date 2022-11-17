#include <SFML/Graphics.hpp>
#include <Windows.h>
#pragma once
class AnimationCaption {
public:
	AnimationCaption();
	AnimationCaption(const wchar_t* name, int posX, int posY, int width, int height, int timeMS);
	AnimationCaption(const wchar_t* name, int posX, int posY, int width, int height, int timeMS, AnimationCaption** toStart);

	void animationWord(sf::RenderWindow& render);
	void start();
	void stop();


private:
	sf::Texture loadTextureFromResource(const wchar_t* name);

	sf::Sprite mainSprite;
	sf::Texture allTexture;
	int sequence_height = 0;
	int sizeWidth;
	int sizeHeight;
	sf::Clock clock;
	int timeToChangeFrame;
	bool display = false;
	AnimationCaption** toStart;
};

