#include "Bullet.h"
#include <iostream>
#include <cmath>

// this is the entry for enemy bullets being created and destroyed off screen

float vectorLength(const sf::Vector2f& vec)
{
    return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}

    // this is initializing the creation of the enemy bullets
Bullet::Bullet(sf::Vector2f startPos, sf::Vector2f targetPos) : active(true), bulletSpd(300.f)
{
    myBullet.setRadius(5.f); // smaller to show enemy shot
    myBullet.setFillColor(sf::Color::Red); // different color to show enemy firing
    myBullet.setPosition(startPos);
    myBullet.setOrigin(myBullet.getRadius(), myBullet.getRadius());

    sf::Vector2f direction = targetPos - startPos;

    float length = vectorLength(direction);
    if (length != 0)
    {
        sf::Vector2f normalizedDirection(direction.x / length, direction.y / length);
        bulletVel = normalizedDirection * bulletSpd; // speed for enemy bullet
    }
    else
    {
        bulletVel = sf::Vector2f(0.f, bulletSpd);
    }
}

    // this is initializing my bullet creation for the player
Bullet::Bullet(sf::Vector2f startPos) : active(true), bulletSpd(200.f)
{
    myBullet.setRadius(10.f);
    myBullet.setFillColor(sf::Color::Yellow);
    myBullet.setPosition(startPos.x + 50.f / 2 - myBullet.getRadius(), startPos.y - myBullet.getRadius());
    bulletVel = sf::Vector2f(0.f, -bulletSpd);
}

void Bullet::update(float deltaTime)
{
    if (active)
    {
        myBullet.move(bulletVel * deltaTime);
        sf::Vector2f pos = myBullet.getPosition();
        float radius = myBullet.getRadius();

        // this is my area check top \ bottom \ left | right
        if (pos.y < -radius || pos.y > 800.f + radius || pos.x < -radius || pos.x > 800.f + radius)
        {
            active = false;
            std::cout << "Bullet Removed (off-screen.)" << std::endl;
        }
    }
}

void Bullet::draw(sf::RenderWindow &window) const
{
    if (active)
    {
        window.draw(myBullet);
    }
}

sf::FloatRect Bullet::getGlobalBounds() const
{
    return myBullet.getGlobalBounds();
}

bool Bullet::isActive() const
{
    return active;
}

void Bullet::deActivate()
{
    active = false;
}

sf::Vector2f Bullet::getPosition() const
{
    return myBullet.getPosition();
}
