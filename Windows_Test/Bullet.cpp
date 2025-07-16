#include "Bullet.h"
#include <iostream>

    // this is initializing my bullet speed
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
        if(myBullet.getPosition().y < -50.f)
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
