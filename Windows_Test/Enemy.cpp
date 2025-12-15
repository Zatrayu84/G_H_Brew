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

bool Enemy::canShoot()
{
    return shootTimer.getElapsedTime().asSeconds() <= shootCooldown;
}

void Enemy::shoot(std::vector<Bullet> &bullets, sf::Sound &pewSound,const sf::Vector2f& targetPos)
{
    Bullet newBullet(enemySprite.getPosition(), targetPos);
    bullets.push_back(newBullet);
    pewSound.play();
    std::cout << "Enemy Bullet Fired!" << std::endl;
    shootTimer.restart(); // this is my timer reset
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