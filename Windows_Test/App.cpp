#include "App.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

    //  Constructor here
myApp::myApp() : newWindow(sf::VideoMode(800, 800), "Galaga_HomeBrew - Erik Segura")
{
    newWindow.setPosition(sf::Vector2i(200, 125));
    loadAssets();
    initializeEnemies(40);
}

    //Functions

void myApp::loadAssets() // this is to also load all assets needed
{
//===========================================================================================================
//  Audio

    // better practice to load all assets in one spot, makes more sense to me
    // load my music
    if (!myAudio.loadMusic("Audio/Title_Screen.wav"))
    {
        std::cout << "Error loading music file: Audio/Title_Screen.wav" << std::endl;
    }
    myAudio.setMusicLoop(true);
    myAudio.playMusic();

    if (!myAudio.loadSoundEffect("Audio/Pew__003.ogg", "pew"))
    {
        std::cout << "Error loading bullet sfx file: Audio/Pew__003.ogg" << std::endl;
    }

    if (!myAudio.loadSoundEffect("Audio/Explosion2__007.ogg", "boom"))
    {
        std::cout << "Error loading GameOverFONT file: Audio/Explosion2__007.oog" << std::endl;
    }

    if (!myAudio.loadSoundEffect("Audio/Starpower__001.ogg", "done"))
    {
        std::cout << "Error loading background texture file: Sprites/space.png"  << std::endl;
    }

//===========================================================================================================
//  Load Fonts

    if (!fontGameOver.loadFromFile("Font/space_age_font.ttf"))
    {
        std::cout << "Error loading GameOverFONT file: Font/space_age_font.ttf" << std::endl;
    }

    // this is for the text to display while setting font settings too
    textGameOver.setFont(fontGameOver);
    textGameOver.setString("GAME OVER \n YOU WIN! \n Hit ENTER to \n close window.");
    textGameOver.setCharacterSize(30);
    textGameOver.setFillColor(sf::Color::Red);
    textGameOver.setStyle(sf::Text::Bold);
    //  center my text
    sf::FloatRect textBounds = textGameOver.getLocalBounds();
    textGameOver.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    float windowCenterX = 800.f / 2.0f;
    float windowCenterY = 800.f / 2.0f;
    textGameOver.setPosition(windowCenterX, windowCenterY);

//=========================================================================================================
//  Textures - BG, ENEMY
    //  load my textures here for BG
    if (!textureBackground.loadFromFile("Sprites/space.png"))
    {
        std::cout << "Error loading texture file: Sprites/space.png" << std::endl;
    }

    textureBackground.setRepeated(true);
    backGround.setTexture(textureBackground);

    // // this is the correct way to set texture and repeat to fill the window size
    backGround.setTextureRect(sf::IntRect(0,0,800,800));

    if (!enemyShipTexture.loadFromFile("Sprites/space_shuttle.png"))
    {
        std::cout << "Error loading texture file: Sprites/space_shuttle.png" << std::endl;
    }
}

void myApp::initializeEnemies(int count)
{
    float enemyWidth = 50.f;
    float enemyHeight = 50.f;
    
    enemies.clear();
    // Parameters for the rows
    const float enemySpacingX = enemyWidth + 10.0f;
    const float enemySpacingY = enemyHeight; //+ 20.0f;

    const int enemiesPerRow = 10;
    
    // Rows calculated here
    const int numRows = (count + enemiesPerRow - 1) / enemiesPerRow;

    // code to get grid semi centered lots of maths
    float totalGridWidth = (enemiesPerRow - 1) * enemySpacingX + enemyWidth;
    float totalGridHeight = (numRows - 1) * enemySpacingY + enemyHeight;

    float winWidth = 800.0f;
    float offsetX = (winWidth - totalGridWidth) / 2.0f;
    offsetX += 40.0f;

    // this is the offset from the top of the window
    float topOfScreen = 20.f;
    float offsetY = topOfScreen + enemyHeight;

    // need to make sure that my horizontal offset isn't offscreen
    if (offsetX < 0) 
    {
        offsetX = 0;
    }

    // Loop to create the enemeis in a now centered grid pattern
    for (int i = 0; i < count; ++i)
    {
        // calculate the rows and columns based on my "i" index
        int currentRow = i / enemiesPerRow;
        int currentColumn = i % enemiesPerRow;
        
        // Enemies X and Y positions
        float enemyX_Relative = (currentColumn * enemySpacingX);
        float enemyY_Relative = (currentRow * enemySpacingY);

        // centering in relation to my new grid parameters
        float finalEnemyX = offsetX + enemyX_Relative;
        float finalEnemyY = offsetY + enemyY_Relative;

        // enemy positions and textures loaded
        enemies.push_back(Enemy(finalEnemyX, finalEnemyY, enemyShipTexture)); // this creates my enemies
    }
    std::cout << "Initialized " << enemies.size() << " enemies in pattern." << std::endl;
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
        newWindow.clear(sf::Color::Black); 
        newWindow.setView(newWindow.getDefaultView());
        newWindow.draw(backGround);

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
        newWindow.display();
}




