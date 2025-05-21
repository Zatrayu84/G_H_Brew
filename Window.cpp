#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


int main () {
    sf::Window Galaga_Window(sf::VideoMode(600, 600), "Galaga Home Brew");

    while (Galaga_Window.isOpen()) {

        sf::Event event;
        
        // check for events that may be triggered in previous iterations
        while (Galaga_Window.pollEvent(event)) {

            // now we check for a close event request
            if (event.type == sf::Event::Closed)
                Galaga_Window.close();
        }
    }
    return 0;
}

