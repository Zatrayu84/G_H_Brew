#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Bullet
{
public:
    //Constructor
    Bullet(sf::Vector2f startPos);

    // my Function 
    void update(float deltaTime);
    void draw(sf::RenderWindow &window);
    sf::FloatRect getGlobalBounds() const;
    bool isActive() const;
    void deActivate();  //  going to use this for killing the bullet off screen
    sf::Vector2f getPosition() const;

private:
    sf::CircleShape myBullet;
    sf::Vector2f bulletVel;
    bool active;
    float bulletSpd;
};