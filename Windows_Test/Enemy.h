#pragma once
#include <SFML/Graphics.hpp>

class Enemy
{
public:
    // Constructor here
    Enemy(float xPos, float yPos);

    //  Functions go here
    void Draw(sf::RenderWindow &window);
    sf::FloatRect getGlobalBounds() const;

private:
    //  This is my enemy shape build
    sf::CircleShape myEnemy;
};