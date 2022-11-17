#include "ManagerCards.h"
#include <iostream>


ManagerCards::ManagerCards(sf::RenderWindow* window) {
    cards_player[0] = new Card(loadTextureFromResource(L"IDB_0"), 27,260, false, 0);
    cards_player[1] = new Card(loadTextureFromResource(L"IDB_1"), 48, 208, false, 1);
    cards_player[2] = new Card(loadTextureFromResource(L"IDB_2"), 69,260, false, 2);
    cards_player[3] = new Card(loadTextureFromResource(L"IDB_3D"), 90,208, false, 3);
    cards_player[4] = new Card(loadTextureFromResource(L"IDB_4"), 111, 260, false, 4);
    cards_player[5] = new Card(loadTextureFromResource(L"IDB_5"), 132,208, false, 5);
    cards_player[6] = new Card(loadTextureFromResource(L"IDB_6"), 153,260, false, 6);
    cards_player[7] = new Card(loadTextureFromResource(L"IDB_7"), 174,208, false, 7);
    cards_player[8] = new Card(loadTextureFromResource(L"IDB_8"), 195,260, false, 8);
    
    cards_bot[0] = new Card(loadTextureFromResource(L"IDB_0"), 27, 39, true, 0);
    cards_bot[1] = new Card(loadTextureFromResource(L"IDB_1"), 48, 91, true, 1);
    cards_bot[2] = new Card(loadTextureFromResource(L"IDB_2"), 69, 39, true, 2);
    cards_bot[3] = new Card(loadTextureFromResource(L"IDB_3D"), 90, 91, true, 3);
    cards_bot[4] = new Card(loadTextureFromResource(L"IDB_4"), 111, 39, true, 4);
    cards_bot[5] = new Card(loadTextureFromResource(L"IDB_5"), 132, 91, true, 5);
    cards_bot[6] = new Card(loadTextureFromResource(L"IDB_6"), 153, 39, true, 6);
    cards_bot[7] = new Card(loadTextureFromResource(L"IDB_7"), 174, 91, true, 7);
    cards_bot[8] = new Card(loadTextureFromResource(L"IDB_8"), 195, 39, true, 8);

    rozlosujKarty(cards_bot);

    emptyCardWhite = loadTextureFromResource(L"IDB_WHITE_CARD");
    emptyCardBlack = loadTextureFromResource(L"IDB_BLACK_CARD");
    texDeleted = loadTextureFromResource(L"IDB_DELETED");
    
    deletedSprite.setTexture(texDeleted);

    rect.setFillColor(sf::Color(155, 3, 3));
    rect.setSize(sf::Vector2f(55, 4));
    rect.setOrigin(27.5, 2);

    this->window = window;

    animPlayer = new AnimationCard(Point{ 291,249}, &emptyCardWhite, &emptyCardBlack);
    animBot = new AnimationCard(Point{ 291,105}, &emptyCardWhite, &emptyCardBlack);
 

    caption_poswiataKarty = new AnimationCaption(L"IDB_KARTAMIGOTAJACA", 291, 249, 41, 51, 60);
    caption_twojRuch = new AnimationCaption(L"IDB_TWOJRUCH", 65, 150, 137, 54, 60, &caption_poswiataKarty);

    cap_napisA = new Caption(sf::Vector2f(130,160));
    
    pkt_gracz = new Caption(sf::Vector2f(312, 204), "0");
    pkt_bot = new Caption(sf::Vector2f(312, 60), "0");

    rozpocznijGre();
}




void ManagerCards::draw(sf::RenderWindow& renderWindow) {
    //Rysowanie kart Gracza
    for (int i = 0; i < 9; i++) {
        Card* card = cards_player[i];

        //Ukryte lub widoczne karty
        if (card->isHide()) {
            int nbm = card->getNumber();
            emptySprite.setPosition(card->getSprite().getPosition());
            if (nbm == 1 || nbm == 3 || nbm == 5 || nbm == 7) {
                emptySprite.setTexture(emptyCardWhite);
            }
            else {
                emptySprite.setTexture(emptyCardBlack);
            }
            renderWindow.draw(emptySprite);
        }
        else 
            renderWindow.draw(card->getSprite());
        //Skreslone karty
        if (card->isDeleted()) {
            rect.setPosition(sf::Vector2f(card->getSprite().getPosition().x + 20, card->getSprite().getPosition().y + 25));
            rect.setRotation(53);
            renderWindow.draw(rect);
            rect.setRotation(127);
            renderWindow.draw(rect);
        }


    }
    //Rysowanie kart bota
    for (int i = 0; i < 9; i++) {
        Card* card = cards_bot[i];
        if (card->isHide()) {
            //Ukryte lub widoczne karty
            int nbm = card->getNumber();
            emptySprite.setPosition(card->getSprite().getPosition());
            if (nbm == 1 || nbm == 3 || nbm == 5 || nbm == 7) {
                emptySprite.setTexture(emptyCardWhite);
            }
            else {
                emptySprite.setTexture(emptyCardBlack);
            }
            renderWindow.draw(emptySprite);
        }
        else
            renderWindow.draw(card->getSprite());
        //Skreslone karty
        if (card->isDeleted()) {
            rect.setPosition(sf::Vector2f(card->getSprite().getPosition().x + 20, card->getSprite().getPosition().y + 25));
            rect.setRotation(53);
            renderWindow.draw(rect);
            rect.setRotation(127);
            renderWindow.draw(rect);
        }
    }
    //Rysowanie przesuwaj¹cych sie kart
    if (animPlayer->getCardToAnim() != nullptr) {
        animPlayer->animation(renderWindow);
    }
    if (animBot->getCardToAnim() != nullptr) {
        animBot->animation(renderWindow);
    }
    
    //Ostatnie
    caption_twojRuch->animationWord(renderWindow);
    caption_poswiataKarty->animationWord(renderWindow);

    //Rysowanie napisow
    cap_napisA -> draw(renderWindow);
    pkt_gracz->draw(renderWindow);
    pkt_bot->draw(renderWindow);
}
void ManagerCards::update(sf::RenderWindow& window) {
    checkStateGame();
    animPlayer->update(window);
    animBot->update(window);
  
}

void ManagerCards::click() {
    if (blockClickPlayer) {
        return;
    }
    int x = sf::Mouse::getPosition(*window).x;
    int y = sf::Mouse::getPosition(*window).y;

    for (int i = 0; i < 9; i++) {
        Card* card = cards_player[i];
        if (isCollision(card->getSprite().getGlobalBounds(), x, y)) {
            if (!card->isDeleted()) {
                card->putDelet();
                player_bot = true;
                animPlayer->copyCardToAnim(*card, false);
                blockClickPlayer = true;
                caption_twojRuch->stop();
            }
        }
         
    }
}

void ManagerCards::checkStateGame() {
    if(!block_moveCards) {
        if (!player_bot ) {
            caption_twojRuch->start();
            blockClickPlayer = false;
        
        }
        else if (player_bot ) {
            blockClickPlayer = true;
            caption_twojRuch->stop();
            moveBot();
        }
    }

    //Jesli sa 2 karty przyznaje pkt 
    if (animPlayer->getCardToAnim()!=nullptr && animBot->getCardToAnim()!= nullptr) {
        //Sprawdzanie kto wygral runde
        bool playerpkt = false;
        bool botpkt = false;
        bool rowne = false;

        block_moveCards = true;
        blockClickPlayer = true;
        caption_twojRuch->stop();

        if (animPlayer->isCardOnSide() && animBot->isCardOnSide()) {
            Card* a = animPlayer->getCardToAnim();
            Card* b = animBot->getCardToAnim();

            if (a->getNumber() > b->getNumber()) {
                //Wygrywa gracz
                cap_napisA->setText("Twoja karta jest wieksza\n             Zwyciestwo");
                playerpkt = true;
                
            }
            else if (a->getNumber() < b->getNumber()) {
                //Wygrywa bot
                cap_napisA->setText("Twoja karta jest wieksza\n              Porazka");
                botpkt = true;
            }
            else if (a->getNumber() == b->getNumber()) {
                //Kart ==
                rowne = true;
                cap_napisA->setText("Karty sa rowne");
            }
            if (cl_twoCardOnSide.getElapsedTime().asMilliseconds() > 350) {
                animPlayer->removeCard();
                animBot->removeCard();
                cap_napisA->setVisible(false);
                block_moveCards = false;
                blockClickPlayer = false;
                if (playerpkt)
                    pointPlayer++;
                else if (botpkt)
                    pointBot++;

                pkt_bot->setText(std::to_string(pointBot));
                pkt_gracz->setText(std::to_string(pointPlayer));

            }                
        }
        else {
            cl_twoCardOnSide.restart();
        }
    }
  
    //jesli wszystkie karty sa w stanie delete to gra zaczyna sie od nowa
    bool findCardNotDeletedA = false;
    for (int i = 0; i < 9; i++) {
        if (!cards_player[i]->isDeleted() || !cards_bot[i]->isDeleted()) {
            findCardNotDeletedA = true;
            break;
        }
    }
    if (!findCardNotDeletedA) {
        if (cl_coutToEnd.getElapsedTime().asMilliseconds() > 2000) {
            rozpocznijGre();
        }

    }
    else {
        cl_coutToEnd.restart();
    }

}
void ManagerCards::rozpocznijGre() {
    animPlayer->removeCard();
    animBot->removeCard();

    resetKart();
    rozlosujKarty(cards_bot);
   

    std::cout << "Rozpoczeto gre" << std::endl;

    caption_twojRuch->stop();
    block_moveCards = false;
    cap_napisA->setVisible(false);

    //Losowanie kto zaczyna gre
    if (random_mt19937(0,1) == 0) {
        std::cout << "rozpoczyna gracz" << std::endl;
        player_bot = false;
        caption_twojRuch->start();
    }
    else {
        //random_time = random_mt19937(200, 500);
        std::cout << "rozpoczyna bot" << std::endl;
        player_bot = true;
    }
    
}

void ManagerCards::moveBot() {
    if (first_moveBot) {
        first_moveBot = false;
        cl_coutDownMoveBot.restart();
    }
    else if(cl_coutDownMoveBot.getElapsedTime().asMilliseconds() > 100) {
        //Wylosuj karte
        if (cards_bot_chosen.size() > 0){
            int index_card = random_mt19937(0, cards_bot_chosen.size()-1);
            int number_card = cards_bot_chosen[index_card];

            cout << "Bot wyloswal :" << number_card << endl;
            cards_bot_chosen.erase(cards_bot_chosen.begin()+ index_card);                      
            
            cards_bot[number_card]->putDelet();
            animBot->copyCardToAnim(*cards_bot[number_card], true);
            
            blockClickPlayer = false;
            player_bot = false;
            first_moveBot = true;
        }
    }
}

Card** ManagerCards::getCardsPlayer() {
    return cards_player;
}
Card** ManagerCards::getCardsBots() {
    return cards_bot;
}


sf::Texture ManagerCards::loadTextureFromResource(const wchar_t* name) {
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

bool ManagerCards::isCollision(sf::FloatRect rect, int posX, int posY) {
    if (posX > rect.left * scale && posX < rect.left * scale + rect.width * scale && posY > rect.top * scale && posY < rect.top * scale + rect.height * scale) {
        return true;
    }

    return false;
}


sf::Texture& ManagerCards::getBlackTextureCard() {
    return this->emptyCardBlack;
}
sf::Texture& ManagerCards::getWhiteTextureCard() {
    return this->emptyCardWhite;
}
void ManagerCards::setScale(float scale) {
    this->scale = scale;
}

int ManagerCards::random_mt19937(int min, int max) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(min, max);
    return dist6(rng);
}

void ManagerCards::rozlosujKarty(Card** cards) {
    sf::Vector2f posCardA;
    sf::Vector2f posCardB;
    
    for (int i = 0; i < 100; i++) {
        int n = random_mt19937(0, 8);
        if (n == 1 || n == 3 || n == 5 || n == 7) {
            posCardA = cards[1]->getSprite().getPosition();
            posCardB = cards[n]->getSprite().getPosition();
            cards[1]->getSprite().setPosition(posCardB);
            cards[n]->getSprite().setPosition(posCardA);
        }
        else {
            posCardA = cards[0]->getSprite().getPosition();
            posCardB = cards[n]->getSprite().getPosition();
            cards[0]->getSprite().setPosition(posCardB);
            cards[n]->getSprite().setPosition(posCardA);
        }
    }
    
    setVisibleAllCards(cards_bot, true);
}

void ManagerCards::setVisibleAllCards(Card** cards, bool isHide) {
    for (int i = 0; i < 9; i++) {
        cards[i]->setHide(isHide);
    }
}

void ManagerCards::resetKart() {
    for (int i = 0; i < 9; i++) {
        cards_player[i]->undoDelete();
        cards_bot[i]->undoDelete();
    }

    cards_bot_chosen.clear();
    for (int i = 0; i < 9; i++) {
        cards_bot_chosen.push_back(i);
    }

    pointBot = 0;
    pointPlayer = 0;
    pkt_gracz->setText(std::to_string(pointPlayer));
    pkt_bot->setText(std::to_string(pointBot));

}

