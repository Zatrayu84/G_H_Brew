#include "App.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

    //  Constructor here
myApp::myApp() : newWindow(sf::VideoMode(800, 800), "Galaga_HomeBrew - Erik Segura")
{
    newWindow.setPosition(sf::Vector2i(200, 125));

}

    //Functions

void myApp::loadAssets() // this is to also load all assets needed
{
//===========================================================================================================
//  Audio

    // better practice to load all assets in one spot, makes more sense to me
    // load my music
    if (!myAudio.loadMusic("Title_Screen.wav"))
    {
        std::cout << "Error loading file." << std::endl;
    }
    myAudio.setMusicLoop(true);
    myAudio.playMusic();

    if (myAudio.loadSoundEffect("Pew__003.ogg", "pew"))
    {
        std::cout << "Error loading bullet sfx file." << std::endl;
    }

    if (myAudio.loadSoundEffect("Explosion2__007.ogg", "boom"))
    {
        std::cout << "Error loading explosion sfx file." << std::endl;
    }

    if (myAudio.loadSoundEffect("Starpower__001.ogg", "done"))
    {
        std::cout << "Error loading GameOver sfx file." << std::endl;
    }

//===========================================================================================================
//  Load Fonts

    if (!fontGameOver.loadFromFile("Space age.tff"))
    {
        std::cout << "Error loading GameOverFONT file." << std::endl;
    }

    // this is for the text to display while setting font settings too
    textGameOver.setFont(fontGameOver);
    textGameOver.setString("GAME OVER \n YOU WIN! \n Hit ENTER to \n close window.");
    textGameOver.setCharacterSize(30);
    textGameOver.setFillColor(sf::Color::Red);
    textGameOver.setStyle(sf::Text::Bold);
    textGameOver.setPosition((800/2) - 100, (800/2) - 50);

//=========================================================================================================
//  Textures - BG
    //  load my textures here for BG
    if (!texture.loadFromFile("space.png"))
    {
        std::cout << "Error loading texture file." << std::endl;
    }

    texture.setRepeated(true);
    sf::Sprite backGround;
    backGround.setTexture(texture);

    // // this is the correct way to set texture and repeat to fill the window size
    backGround.setTextureRect(sf::IntRect(0,0,800,800));
}

void myApp::initializeEnemies(int count)
{
    // create and seeding the random enemies and positions
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (int i = 0 ; i < count; ++i)
    {
        float ranX = static_cast<float>(std::rand() % (800 - 70));
        float ranY = static_cast<float>(std::rand() % (200));
        enemies.push_back(Enemy(ranX + 20, ranY));
    }
}

//  Here is my Game Manager
void myApp::runMe()
{
    while (newWindow.isOpen())
    {
        float deltaTime = myClock.restart().asSeconds();
        handleEvents();
        updateLogic(deltaTime);
        render();
    }
}

void myApp::handleEvents() 
{
    sf::Event event;
    while (newWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            std::cout << "This is now closed" << std::endl;
            newWindow.close();
        }
        // this is the projectile movement on trigger
        if (event.type == sf::Event::KeyPressed)
        {
            if (!goTextActive)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    myPlayer.shoot(bullets, myAudio.getSoundEffect("pew"));
                }
            }
            else
            {
                if (event.key.code == sf::Keyboard::Enter)
                {
                    std::cout << "Window was closed by 'Enter Key'!" << std::endl;
                    newWindow.close();
                }
            }
            
        }
    }
}

void myApp::updateLogic(float deltaTime)
{
    if (!goTextActive)
    {
        // this is where my player moves
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
        myPlayer.move(-.5f, 0.f);  // this should allow movement to the left or negative x
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            myPlayer.move(.5f, 0.f); // this should allow movement to the right or positive x
        }

        //this is where my bullets update and detect collision
        for (auto bulletIter = bullets.begin(); bulletIter != bullets.end();)
        {
            bulletIter->update(deltaTime);
            if (!bulletIter->isActive())
            {
                bulletIter = bullets.erase(bulletIter);
                continue;
            }

            bool collisionOccured = false;
            for (auto enemyIter = enemies.begin(); enemyIter != enemies.end();)
            {
                if (bulletIter->getGlobalBounds().intersects(enemyIter->getGlobalBounds()))
                {
                    std::cout << "Collision has happened!" << std::endl;
                    enemyIter = enemies.erase(enemyIter);
                    myAudio.getSoundEffect("boom").play();
                    bulletIter->deActivate();
                    collisionOccured = true;
                    break;
                }
                else
                {
                    ++enemyIter;
                }
            }
            if (collisionOccured)
            {
                bulletIter = bullets.erase(bulletIter);
            }
            else
            {
                ++bulletIter;
            }

            // adding my game over check here
            if (enemies.empty() && !goTextActive)
            {
                goTextActive = true;
                myAudio.getSoundEffect("done").play();
                std::cout << "Game Over, all enemies have been destroyed" << std::endl;
            }
        }
    }
}

void myApp::render()
{
    //  In between the clear call and the display call is where we send the render requests for our items

        // this is to clear the windows out after all items have been rendered
        newWindow.clear(sf::Color::Black); // <-- When we call clear this is also mandatory 
                                          // this is calling the clear to draw the BG???

        // small note, the order in which you draw items is reversed like the stack
        // Last one in first one out
        newWindow.draw(background);

        // here is mu check for the game over text
        if (!goTextActive)
        {
            myPlayer.draw(newWindow);
            // enemies
            for (const auto& enemy : enemies)
            {
                enemy.draw(newWindow);
            }
            for (auto& bullet : bullets)
            {
                bullet.draw(newWindow);
            }
        }
        else
        {
            newWindow.draw(textGameOver);
        }

        // this is mandatory to actually draw what all has been called per ^^^ code
        newWindow.display();  // <-- this is the command to display all rendered requests
}




