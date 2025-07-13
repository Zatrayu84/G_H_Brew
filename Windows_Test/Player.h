#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Bullet.h"
#include <vector>

class Player
{
public:
    //  Constructor
    Player();

    //  Functions
    void move(float offsetX, float offsetY);
    void shoot(std::vector<Bullet> &bullets, const sf::Sound &pewSound);
    void draw(sf::RenderWindow &window);
    sf::FloatRect getGlobalBounds() const;
    sf::Vector2f getPosition() const;

private:
    sf::RectangleShape myPlayer;
    float playerSpeed; // A member variable for player speed
};