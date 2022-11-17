#include "ManagerCards.h"
#include <iostream>

sf::Texture LoadTexture(const wchar_t* name) {
    HRSRC rsrcData = FindResource(NULL, name, RT_RCDATA);
    DWORD rsrcDataSize = SizeofResource(NULL, rsrcData);
    HGLOBAL grsrcData = LoadResource(NULL, rsrcData);
    LPVOID firstByte = LockResource(grsrcData);

    sf::Texture texture;
    if (texture.loadFromMemory(firstByte, rsrcDataSize)) {
        return texture;
        std::cout << "asd" << std::endl;
    }
    else {
        return texture;
    }
}



void AddMenu(HMENU& hMenu, std::string text, const int ID) {
    std::wstring n(text.begin(), text.end());
    AppendMenuW(hMenu, MF_STRING , ID, n.c_str());
}

void MenuAction(int ID, HWND& Window, HWND& ChildWindow, int& WIDTH, int& HEIGHT, ManagerCards& managerCards, sf::View& view) {
    //Window size 740, 660

    switch (ID) {
        case 0:
            SetWindowPos(Window, NULL, WIDTH/2- (370+15)/2,HEIGHT/2-(330+58)/2, 370 + 15, 330 + 58, SWP_SHOWWINDOW);
            view.setViewport(sf::FloatRect(0,0,1,1));
            managerCards.setScale(1);
            break;
        case 1:
            SetWindowPos(Window, NULL, WIDTH / 2 - (555 + 15)/2, HEIGHT/2 - (495 + 58)/2, 555 + 15, 495 + 58, SWP_SHOWWINDOW);
            view.setViewport(sf::FloatRect(0, 0, 1.5, 1.5));
            managerCards.setScale(1.5);
            break;
        case 2:
            SetWindowPos(Window, NULL, WIDTH / 2 - (740 + 15) / 2, HEIGHT / 2 - (660 + 58) / 2, 740 + 15, 660 + 58, SWP_SHOWWINDOW);
            view.setViewport(sf::FloatRect(0, 0, 2, 2));
            managerCards.setScale(2);
            break;
        case 3:
            managerCards.rozpocznijGre();
            break;
    }
}

