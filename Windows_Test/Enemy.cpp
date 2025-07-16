#include "Enemy.h"

Enemy::Enemy(float xPos, float yPos)
{
    myEnemy.setRadius(10.f);
    myEnemy.setFillColor(sf::Color::Green);
    myEnemy.setOutlineThickness(1.0f);
    myEnemy.setOutlineColor(sf::Color::White);
    myEnemy.setPosition(xPos, yPos);
}

void Enemy::draw(sf::RenderWindow &window) const
{
    window.draw(myEnemy);
}

sf::FloatRect Enemy::getGlobalBounds() const
{
    return myEnemy.getGlobalBounds();
}