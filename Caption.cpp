#include "Caption.h"
Caption::Caption() {}

Caption::Caption(sf::Vector2f pos) {
    this->font = LoadFont(L"IDB_FONT");
    text.setPosition(pos);
    text.setStyle(sf::Text::Bold);
    text.setLetterSpacing(-0.1f);
    text.setCharacterSize(15);
    text.setFont(font);
    text.setFillColor(sf::Color::Yellow);
}
Caption::Caption(sf::Vector2f pos, std::string textDisplay) {
    this->font = LoadFont(L"IDB_FONT");
    text.setPosition(pos);
    text.setStyle(sf::Text::Bold);
    text.setLetterSpacing(-0.2f);
    text.setCharacterSize(15);
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    setText(textDisplay);
    visible = true;
}


void Caption::draw(sf::RenderWindow& render) {
    if(visible)
        render.draw(text);
}

void Caption::setText(std::string text) {
    this->setVisible(true);
    this->text.setString(text);
    this->text.setOrigin(this->text.getGlobalBounds().width / 2, 0);
}
void Caption::setVisible(bool visible) {
    this->visible = visible;
}


sf::Font Caption::LoadFont(const wchar_t* name) {
    HRSRC rsrcData = FindResource(NULL, name, RT_RCDATA);
    DWORD rsrcDataSize = SizeofResource(NULL, rsrcData);
    HGLOBAL grsrcData = LoadResource(NULL, rsrcData);
    LPVOID firstByte = LockResource(grsrcData);

    sf::Font font;
    if (font.loadFromMemory(firstByte, rsrcDataSize)) {
        return font;
    }
    else {
        return font;
    }
}