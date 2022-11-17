#include "AnimationCaption.h"

AnimationCaption::AnimationCaption() {}

AnimationCaption::AnimationCaption(const wchar_t* name, int posX, int posY, int width, int height, int timeMS) {
    allTexture = sf::Texture();
    allTexture = loadTextureFromResource(name);

    mainSprite = sf::Sprite();
    mainSprite.setPosition(posX, posY);
    mainSprite.setTexture(allTexture);

    this->sizeWidth = width;
    this->sizeHeight = height;
    this->timeToChangeFrame = timeMS;
    this->toStart = nullptr;
}
AnimationCaption::AnimationCaption(const wchar_t* name, int posX, int posY, int width, int height, int timeMS, AnimationCaption** toStart) {
    allTexture = sf::Texture();
    allTexture = loadTextureFromResource(name);

    mainSprite = sf::Sprite();
    mainSprite.setPosition(posX, posY);
    mainSprite.setTexture(allTexture);

    this->sizeWidth = width;
    this->sizeHeight = height;
    this->timeToChangeFrame = timeMS;
    this->toStart = toStart;
}



void AnimationCaption::animationWord(sf::RenderWindow& render) {
    if (!display)return;

    mainSprite.setTextureRect(sf::IntRect(0, sizeHeight*sequence_height,sizeWidth, sizeHeight));
    render.draw(mainSprite);
  
    if (clock.getElapsedTime().asMilliseconds() > timeToChangeFrame) {
        clock.restart();
        sequence_height++;

        if (sequence_height >= 10 ) {
            sequence_height = 0;
        }

    }

}

void AnimationCaption::start() {
    if (!display) {
        display = true;
        sequence_height = 0;
        if (toStart != nullptr) {
            (*toStart)->start();
        }
    }
}
void AnimationCaption::stop() {
    display = false;
    if (toStart != nullptr) {
        (*toStart)->stop();
    }
}


sf::Texture AnimationCaption::loadTextureFromResource(const wchar_t* name) {
    HRSRC rsrcData = FindResource(NULL, name, RT_RCDATA);
    DWORD rsrcDataSize = SizeofResource(NULL, rsrcData);
    HGLOBAL grsrcData = LoadResource(NULL, rsrcData);
    LPVOID firstByte = LockResource(grsrcData);

    sf::Texture texture;
    if (texture.loadFromMemory(firstByte, rsrcDataSize)) {
        return texture;
    }
    return texture;
}