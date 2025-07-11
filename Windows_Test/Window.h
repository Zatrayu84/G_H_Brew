#pragma once
#include <SFML/Graphics.hpp>

// sf::renderwindow is also used once you are going to start drawing and rending objects within the window
    sf::RenderWindow newWindow(sf::VideoMode(800, 800), "My Window");
    newWindow.setPosition(sf::Vector2i(200, 125));

//===========================================================================================================