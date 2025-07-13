#include "Player.h"
#include <iostream>

Player::Player() : playerSpeed(0.5f)
{
    sf::RectangleShape player(sf::Vector2f(100.f, 100.f));
    myPlayer.setSize(sf::Vector2f(50.f, 50.f));
    myPlayer.setFillColor(sf::Color::Red);
    myPlayer.setOutlineThickness(2.f);
    myPlayer.setOutlineColor(sf::Color::White);
    myPlayer.setPosition(20.f, 745.f);  //set location to bottom of screen
}

void Player::move(float offsetX, float offsetY)
{
    myPlayer.move(offsetX * playerSpeed, offsetY * playerSpeed);

    //  This is for player bounds
    sf::Vector2f pos = myPlayer.getPosition();
    if (pos.x < 0) 
    {
        myPlayer.setPosition(0.f, pos.y);
    }
    
    if (pos.x > 750)
    {
        myPlayer.setPosition(749, pos.y);
    }
}

void Player::shoot(std::vector<Bullet> &bullets, const sf::Sound &pewSound)
{
    Bullet newBullet(myPlayer.getPosition());
    bullets.push_back(newBullet);
    pewSound.play();
    std::cout << "Bullet Fired!" << std::endl;
}

void Player::draw(sf::RenderWindow &window)
{
    window.draw(myPlayer);
}

sf::FloatRect Player::getGlobalBounds() const
{
    return myPlayer.getGlobalBounds();
}

sf::Vector2f Player::getPosition() const
{
    return myPlayer.getPosition();
}

