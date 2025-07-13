#include "Enemy.h"

Enemy::Enemy(float xPos, float yPos)
{
    myEnemy.setRadius(20.f);
    myEnemy.setFillColor(sf::Color::Green);
    myEnemy.setOutlineThickness(1.0f);
    myEnemy.setOutlineColor(sf::Color::White);
    myEnemy.setPosition(xPos, yPos);
}

void Enemy::Draw(sf::RenderWindow &window)
{
    window.draw(myEnemy);
}

sf::FloatRect Enemy::getGlobalBounds() const
{
    return myEnemy.getGlobalBounds();
}