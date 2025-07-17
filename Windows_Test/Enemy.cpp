#include "Enemy.h"
#include <iostream>

Enemy::Enemy(float xPos, float yPos, const sf::Texture& enemyTexture)
{
    enemySprite.setTexture(enemyTexture);
    enemySprite.setRotation(180.0f);
    float baseSize = 50.0f;
    enemySprite.setScale(baseSize / enemyTexture.getSize().x, baseSize / enemyTexture.getSize().y);
    enemySprite.setPosition(xPos, yPos);
}

void Enemy::draw(sf::RenderWindow &window) const
{
    window.draw(enemySprite);
}

sf::FloatRect Enemy::getGlobalBounds() const
{
    return enemySprite.getGlobalBounds();
}

sf::Vector2f Enemy::getPosition() const{
    return enemySprite.getPosition();
}