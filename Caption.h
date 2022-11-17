#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
using namespace std;

class Caption {
public:
	Caption();
	Caption(sf::Vector2f pos);
	Caption(sf::Vector2f pos, std::string textDisplay);
	void draw(sf::RenderWindow& render);
	void setText(std::string text);
	void setVisible(bool visible);

private:
	static sf::Font LoadFont(const wchar_t* name);
	sf::Font font;
	sf::Text text;
	bool visible = false;
};