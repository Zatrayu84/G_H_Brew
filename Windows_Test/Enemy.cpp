#include "Enemy.h"
#include <iostream>

Enemy::Enemy(float xPos, float yPos, const sf::Texture& enemyTexture)
{
    enemySprite.setTexture(enemyTexture);

    float baseSize = 50.0f;
    enemySprite.setScale(baseSize / enemyTexture.getSize().x, baseSize / enemyTexture.getSize().y);

    // Here I had to change my texture scale before rotating it the 180 deg
    sf::Vector2u texSize = enemyTexture.getSize();
    enemySprite.setOrigin(texSize.x / 2.0f, texSize.y / 2.0f);
    enemySprite.setRotation(180.0f);
    enemySprite.setPosition(xPos, yPos);

    //timer set for random shooting
    float minTimer = 1.0f;
    float maxTimer = 8.0f;
    shootCooldown = minTimer + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / (maxTimer - minTimer));

    shootTimer.restart();
}

bool Enemy::canShoot() const
{
    return shootTimer.getElapsedTime().asSeconds() >= shootCooldown;
}

void Enemy::shoot(std::vector<Bullet> &bullets, sf::Sound &pewSound,const sf::Vector2f& targetPos)
{
    Bullet newBullet(getPosition(), targetPos);
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

sf::Vector2f Enemy::getPosition() const
{
    return enemySprite.getPosition();
}