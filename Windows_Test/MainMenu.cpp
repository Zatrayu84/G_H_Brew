#include "MainMenu.h"


MainMenu::MainMenu(float width, float height)
{
    if (!font.loadFromFile("Font/space_age_font.ttf"))
    {
        std::cout << "Error loading file: Font/space_age_font.ttf" << std::endl;
    }

    // menus: Play, Options, About, Exit
    // Menu selections / some dummy selections included play will work to start game.

    //Loop to create my menu items
    for (int i = 0; i < Max_main_menu; ++i)
    {
        mainMenu[i].setFont(font);
        mainMenu[i].setFillColor(sf::Color::White);
        mainMenu[i].setCharacterSize(50);
    }

    //play
    mainMenu[0].setString("Play");
    mainMenu[0].setPosition(width / 2, height / (Max_main_menu + 4) * 3.5f); // Adjusted for better spacing
    mainMenu[0].setOrigin(mainMenu[0].getGlobalBounds().width / 2, mainMenu[0].getGlobalBounds().height / 2);
    //options
    mainMenu[1].setString("Options");
    mainMenu[1].setPosition(width / 2, height / (Max_main_menu + 4) * 4.0f); // Adjusted for better spacing
    mainMenu[1].setOrigin(mainMenu[1].getGlobalBounds().width / 2, mainMenu[1].getGlobalBounds().height / 2);
    //About
    mainMenu[2].setString("Credits");
    mainMenu[2].setPosition(width / 2, height / (Max_main_menu + 4) * 4.5f); // Adjusted for better spacing
    mainMenu[2].setOrigin(mainMenu[2].getGlobalBounds().width / 2, mainMenu[2].getGlobalBounds().height / 2);
    //Exit
    mainMenu[3].setString("Exit");
    mainMenu[3].setPosition(width / 2, height / (Max_main_menu + 4) * 5.0f); // Adjusted for better spacing
    mainMenu[3].setOrigin(mainMenu[3].getGlobalBounds().width / 2, mainMenu[3].getGlobalBounds().height / 2);
    //Default
    MainMenuSelected = -0;
    mainMenu[MainMenuSelected].setFillColor(sf::Color::Red);
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
    if (MainMenuSelected - 1 >= 0)
    {
        mainMenu[MainMenuSelected].setFillColor(sf::Color::White);
        MainMenuSelected--;
        mainMenu[MainMenuSelected].setFillColor(sf::Color::Red);
    }
    else
    {
        mainMenu[MainMenuSelected].setFillColor(sf::Color::White);
        MainMenuSelected = Max_main_menu - 1;
        mainMenu[MainMenuSelected].setFillColor(sf::Color::Red);
    }
}

void MainMenu::movedown()
{
    if (MainMenuSelected + 1 < Max_main_menu)
    {
        mainMenu[MainMenuSelected].setFillColor(sf::Color::White);
        MainMenuSelected++;
        mainMenu[MainMenuSelected].setFillColor(sf::Color::Red);
    }
    else
    {
        mainMenu[MainMenuSelected].setFillColor(sf::Color::White);
        MainMenuSelected = 0;
        mainMenu[MainMenuSelected].setFillColor(sf::Color::Red);
    }
}
