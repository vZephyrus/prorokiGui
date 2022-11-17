#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include "Tool.h"
#include "resource.h"
#include "ManagerCards.h"
#include "AnimationCard.h"

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")


LRESULT CALLBACK OnEvent(HWND Handle, UINT Message, WPARAM WParam, LPARAM LParam);

using namespace std;

HWND MainWindow;
HWND ChildWindow;

sf::Sprite sprite;

int WIDTH = 0;
int HEIGHT = 0;

ManagerCards* manager;
sf::View view;

int main() {
    HINSTANCE hInstance = GetModuleHandle(NULL);

    WNDCLASS WindowClass;
    WindowClass.style = 0;
    WindowClass.lpfnWndProc = &OnEvent;
    WindowClass.cbClsExtra = 0;
    WindowClass.cbWndExtra = 0;
    WindowClass.hInstance = hInstance;
    WindowClass.hIcon = NULL;
    WindowClass.hCursor = 0;
    WindowClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BACKGROUND);
    WindowClass.lpszMenuName = NULL;
    WindowClass.lpszClassName = L"Gra w proroki";
    
    RegisterClass(&WindowClass);

    WIDTH = GetSystemMetrics(SM_CXSCREEN);
    HEIGHT = GetSystemMetrics(SM_CYSCREEN);

    const static int WIDTH_MENU = 370;
    const static int HEIGHT_MENU = 330;

    const static int WIDTH_MARGIN = 15;
    const static int HEIGHT_MARGIN = 58;

    //WS_SYSMENU
    MainWindow = CreateWindow(L"Gra w proroki", L"Gra w proroki",  WS_VISIBLE | WS_SYSMENU,
        WIDTH/2-(WIDTH_MENU+WIDTH_MARGIN)/2, HEIGHT/2-(HEIGHT_MENU+ HEIGHT_MARGIN) /2, WIDTH_MENU+WIDTH_MARGIN, HEIGHT_MENU+HEIGHT_MARGIN
        , NULL, NULL, hInstance, NULL);

    ChildWindow = CreateWindow(L"Static", NULL, WS_CHILD, 0, 0, 740, 660, MainWindow, NULL, hInstance, NULL);

    sf::RenderWindow Area_to_display;
    
    // Or, if you want to do it after construction :
    sf::ContextSettings context;
    context.antialiasingLevel = 16;
    Area_to_display.create(ChildWindow, context);

    sf::Texture texture = LoadTexture(L"IDB_MENU");
    sprite.setTexture(texture);

    //
    manager = new ManagerCards(&Area_to_display);


    //
    HMENU hMainBar = CreateMenu();

    HMENU hThreeGra = CreateMenu();
    AddMenu(hThreeGra, "Rozpocznij gre", 3);
 
    AppendMenuW(hMainBar, MF_POPUP, (UINT_PTR)hThreeGra, L"Gra");

    HMENU hThreeWidok = CreateMenu();
    AddMenu(hThreeWidok, "370 x330", 0);
    AddMenu(hThreeWidok, "555 x 495", 1);
    AddMenu(hThreeWidok, "740 x 660", 2);
    AppendMenuW(hMainBar, MF_POPUP, (UINT_PTR)hThreeWidok, L"Widok");
    
    SetMenu(MainWindow, hMainBar);
    //

    MSG Message;
    Message.message = ~WM_QUIT;
    
    view.setCenter(370, 330);
    view.setSize(sf::Vector2f(740, 660));

    
    while (Message.message != WM_QUIT)
    {
        if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
        {
            // If a message was waiting in the message queue, process it
            TranslateMessage(&Message);
            DispatchMessage(&Message);
        }
        else
        {
            Area_to_display.clear(sf::Color::Black);
            Area_to_display.draw(sprite);

            manager->update(Area_to_display);
            manager->draw(Area_to_display);
            
            Area_to_display.setView(view);
            Area_to_display.display();

            // SFML rendering code goes here
            Sleep(10);
        }
    }

    DestroyWindow(MainWindow);
    UnregisterClass(L"Gra w proroki", hInstance);

    return 0;
}



LRESULT CALLBACK OnEvent(HWND Handle, UINT Message, WPARAM WParam, LPARAM LParam) {
    switch (Message) {
        // Quit when we close the main window
    case WM_CLOSE:
        PostQuitMessage(0);
        return 0;

    case WM_COMMAND:
        MenuAction(WParam, MainWindow, ChildWindow, WIDTH, HEIGHT, *manager, view);
        break;
    case WM_LBUTTONDOWN:
        manager->click();
        break;
    }

    return DefWindowProc(Handle, Message, WParam, LParam);
}