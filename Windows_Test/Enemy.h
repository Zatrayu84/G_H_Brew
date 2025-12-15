#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Bullet.h"

class Enemy
{
private:
    //  This is my enemy shape build
    sf::Sprite enemySprite;
    // Adding timer for enemy shooting timing
    sf::Clock shootTimer;
    float shootCooldown = 2.0f;  // this is going to be measured in seconds

public:
    // Constructor here
    Enemy(float xPos, float yPos, const sf::Texture& enemyTexture);

    //  Functions go here
    void draw(sf::RenderWindow &window) const;
    void shoot(std::vector<Bullet> &bullets, sf::Sound &pewSound,const sf::Vector2f& targetPos);
    sf::FloatRect getGlobalBounds() const;
    sf::Vector2f getPosition() const;
    bool canShoot(); // here we verify if enemy can shoot based on timer
    sf::Vector2f getCenter();
};