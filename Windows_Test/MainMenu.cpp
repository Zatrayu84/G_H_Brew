#include "MainMenu.h"


MainMenu::MainMenu(float width, float height)
{
    if (!font.loadFromFile("Font/space_age_font.ttf"))
    {
        std::cout << "Error loading file: Font/space_age_font.ttf" << std::endl;
    }

    // menus: Play, Options, About, Exit
    // Menu selections / some dummy selections included play will work to start game.

    //play
    mainMenu[0].setFont(font);
    mainMenu[0].setFillColor(sf::Color::White);
    mainMenu[0].setString("Play");
    mainMenu[0].setCharacterSize(70);
    mainMenu[0].setPosition(400, 100);
    //options
    mainMenu[1].setFont(font);
    mainMenu[1].setFillColor(sf::Color::White);
    mainMenu[1].setString("Options");
    mainMenu[1].setCharacterSize(70);
    mainMenu[1].setPosition(400, 200);
    //About
    mainMenu[2].setFont(font);
    mainMenu[2].setFillColor(sf::Color::White);
    mainMenu[2].setString("About");
    mainMenu[2].setCharacterSize(70);
    mainMenu[2].setPosition(400, 300);
    //Exit
    mainMenu[3].setFont(font);
    mainMenu[3].setFillColor(sf::Color::White);
    mainMenu[3].setString("Exit");
    mainMenu[3].setCharacterSize(70);
    mainMenu[3].setPosition(400, 400);

    MainMenuSelected = -1;
}

MainMenu::~MainMenu()
{

}

// Lets draw the menu out here

void MainMenu::draw(sf::RenderWindow &window)
{
    for (int i = 0; i < Max_main_menu; ++i)
    {
        window.draw(mainMenu[i]);
    }
}

// going up
void MainMenu::moveUp()
{
    if (!MainMenuSelected - 1 >= 0)
    {
        mainMenu[MainMenuSelected].setFillColor(sf::Color::White);
        MainMenuSelected--;

        if(MainMenuSelected == -1)
        {
            MainMenuSelected = 2;
        }
        mainMenu[MainMenuSelected].setFillColor(sf::Color::Blue);

    }
}

void MainMenu::movedown()
{
    if (!MainMenuSelected + 1 <= Max_main_menu)
    {
        mainMenu[MainMenuSelected].setFillColor(sf::Color::White);
        MainMenuSelected++;

        if(MainMenuSelected == 4)
        {
            MainMenuSelected = 0;
        }
        mainMenu[MainMenuSelected].setFillColor(sf::Color::Blue);
        
    }
}
