#pragma once
#include <SFML/Graphics.hpp>

class Enemy
{
public:
    // Constructor here
    Enemy(float xPos, float yPos, const sf::Texture& enemyTexture);

    //  Functions go here
    void draw(sf::RenderWindow &window) const;
    sf::FloatRect getGlobalBounds() const;
    sf::Vector2f getPosition() const;


private:
    //  This is my enemy shape build
    sf::Sprite enemySprite;
};