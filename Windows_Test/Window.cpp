#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>


//===========================================================================================================
// This is going to be the area for declarations, in an official build i will be making a seperate header and cpp file for each item

struct Enemy 
{
    sf::CircleShape myEnemy;
};

struct Bullets
{
    sf::CircleShape myBullet;
    sf::Vector2f BulletVel;
    bool BulletActive;
};

Enemy makeEnemy(float xPos, float yPos)
{ 
// this is for the enemies
    Enemy CreateEnemy;
    CreateEnemy.myEnemy.setRadius(20.f);
    CreateEnemy.myEnemy.setFillColor(sf::Color::Green);
    CreateEnemy.myEnemy.setOutlineThickness(1.0f);
    CreateEnemy.myEnemy.setOutlineColor(sf::Color::White);
    CreateEnemy.myEnemy.setPosition(xPos, yPos);
    return CreateEnemy;
}

// variable for speed of item or enemies
    // float speed = 200.f;

    // sf::Clock myClock;

    // check to see if game over message is active
    //bool GO_Text_Active = false;

int main () {
    // // sf::renderwindow is also used once you are going to start drawing and rending objects within the window
    // sf::RenderWindow newWindow(sf::VideoMode(800, 800), "My Window");
    // newWindow.setPosition(sf::Vector2i(200, 125));

//===========================================================================================================



//===========================================================================================================

    // std::vector<Enemy> enemies;
    // std::vector<Bullets> myBullets;
    // int numberOfEnemies = 10;

    // // create and seeding the random enemies and positions
    // std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // for (int i = 0 ; i < numberOfEnemies; ++i)
    // {
    //     float ranX = static_cast<float>(std::rand() % (800 - 70));
    //     float ranY = static_cast<float>(std::rand() % (200));
    //     enemies.push_back(makeEnemy(ranX + 20, ranY));
    // }

//===========================================================================================================

//===MUSIC===

    sf::Music sampleMusic;
    if (!sampleMusic.openFromFile("Title_Screen.wav"))
    {
        return EXIT_FAILURE;
    }
        // This is where we play the music
    sampleMusic.play();
    sampleMusic.setLoop(true);

    //===SFX===

    //Shots fired
    sf::SoundBuffer effect_shot;
    if (!effect_shot.loadFromFile("Pew__003.ogg"))
    {
        return -1;
    }
    sf::Sound pew;
    pew.setBuffer(effect_shot);
    //pew.play(); example of call for sound to play

    //explode - enemy dies
    sf::SoundBuffer effect_xplode;
    if (!effect_xplode.loadFromFile("Explosion2__007.ogg"))
    {
        return -1;
    }
    sf::Sound boom;
    boom.setBuffer(effect_xplode);

    //game over
    sf::SoundBuffer effect_GameOver;
    if (!effect_GameOver.loadFromFile("Starpower__001.ogg"))
    {
        return -1;
    }
    sf::Sound done;
    done.setBuffer(effect_GameOver);

//===========================================================================================================

    // This is the area to load and set fonts for use in the game

    sf::Font font_GameOver;
    if (!font_GameOver.loadFromFile("space age.ttf"))
    {
        return -1;
    }

    // this is for the text to display while setting font settings too
    sf::Text text_GameOver;
    text_GameOver.setFont(font_GameOver);
    text_GameOver.setString("GAME OVER \n YOU WIN! \n Hit ENTER to \n close window.");
    text_GameOver.setCharacterSize(30);
    text_GameOver.setFillColor(sf::Color::Red);
    text_GameOver.setStyle(sf::Text::Bold);
    text_GameOver.setPosition((800/2) - 100, (800/2) - 50);


//===========================================================================================================

    // This is for the sprite - BG
    // sf::Texture texture;
    // if (!texture.loadFromFile("space.png"))
    // {
    // return -1;
    // }

    // // this is to repeat my texture
    // texture.setRepeated(true);

    // // //create the sprite here with texture
    // sf::Sprite backGround;
    // backGround.setTexture(texture);
    
    // // // this is the correct way to set texture and repeat to fill the window size
    // backGround.setTextureRect(sf::IntRect(0,0,800,800));

        
//===========================================================================================================
        
// this is for my block that will move - player
    sf::RectangleShape player(sf::Vector2f(100.f, 100.f));
    player.setSize(sf::Vector2f(50.f, 50.f));

    player.setFillColor(sf::Color::Red);
    player.setOutlineThickness(2.f);
    player.setOutlineColor(sf::Color::White);
    
    //set location to bottom of screen
    player.setPosition(20.f, 745.f);
    
    // bounding box set up
    sf::FloatRect colBox = player.getGlobalBounds();

//===========================================================================================================
    // this where we check for events as long as the window remains open. 
    // THIS ALSO ACTS AS YOUR GAME LOOP

    // while (newWindow.isOpen())
    // {
    //     sf::Event event;

    //     while (newWindow.pollEvent(event))
    //     {
    //         if (event.type == sf::Event::Closed)
    //         {
    //             std::cout << "This is now closed" << std::endl;
    //             newWindow.close();
    //         }
    //                         // this is the projectile movement on trigger
    //         if (event.type == sf::Event::KeyPressed)
    //         {
    //             if (!GO_Text_Active)
    //             {
    //                 if (event.key.code == sf::Keyboard::Space)
    //                 {
    //                     Bullets newBullet;
    //                     sf::Vector2f blockPos = player.getPosition();

    //                     newBullet.myBullet.setRadius(10.f);
    //                     newBullet.myBullet.setFillColor(sf::Color::Yellow);
    //                     newBullet.myBullet.setPosition(blockPos);
    //                     newBullet.BulletVel = sf::Vector2f(0.f, -speed);
    //                     newBullet.BulletActive = true;
                        
    //                     myBullets.push_back(newBullet);

    //                     pew.play();

    //                     std::cout << "Bullet Fired!" << std::endl;
    //                 }
    //             }
    //             else
    //             {
    //                 if (event.key.code == sf::Keyboard::Enter)
    //                 {
    //                     std::cout << "Window was closed by 'Enter Key'!" << std::endl;
    //                     newWindow.close();
    //                 }
    //             }
    //         }
    //     }
        
//===========================================================================================================



//===========================================================================================================

        float deltaTime = myClock.restart().asSeconds();


        // This is the loop check for hits on enemies from bullet to enemy
        //check for active game over text
    if (!GO_Text_Active)
    {
        // This is for the movement of the player 
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            player.move(-.5f, 0.f);  // this should allow movement to the left or negative x
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            player.move(.5f, 0.f); // this should allow movement to the right or positive x
        }
        
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        // {
        //     player.move(0.f, -.5f); // this should allow movement to the right or positive x
        // }

        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        // {
        //     player.move(0.f, .5f); // this should allow movement to the right or positive x
        // }

        // this is foror border detection
        sf::Vector2f blockPos = player.getPosition();
        if (blockPos.x < 0) player.setPosition(0, blockPos.y);
        if (blockPos.x > 750) player.setPosition(725, blockPos.y);

        // Bullet and enemy movement logic
        for (auto iter = myBullets.begin(); iter != myBullets.end(); )
        {
            if (iter->BulletActive)
            {
                iter->myBullet.move(iter->BulletVel.x * deltaTime, iter->BulletVel.y * deltaTime); // vector for bullets to iter through
                
                bool colHit = false; // this is the check to see if the collision happens.


                sf::FloatRect colBullet = iter->myBullet.getGlobalBounds();

                for (auto iterEnemy = enemies.begin();iterEnemy != enemies.end(); ) // enemy vector to iter through
                {
                    sf::FloatRect colEnemy = iterEnemy->myEnemy.getGlobalBounds(); // Why is this not working this time

                    if (colBullet.intersects(colEnemy))
                    {
                        std::cout << "Colission has occured" << std::endl;
                    

                        //to remove the enemy if it hits
                        iterEnemy = enemies.erase(iterEnemy);
                        boom.play();

                        colHit = true;
                        break; // Exit loop here
                    }
                    // if the enemy is = 0 then clear screen and show text GAME OVER YOU WIN!
                    else
                    {
                        ++iterEnemy;
                    }
                }
                
                //This is the check to see if bullet is off screen
                if (colHit || iter->myBullet.getPosition().y < -20.f)
                {
                    if(iter->myBullet.getPosition().y < -20.f)
                    {
                        std::cout << "Bullet Removed (off-Screen.)" << std::endl;
                    }
                    iter = myBullets.erase(iter);
                }
                else
                {
                    ++iter;
                }
            }
            else
            {
                ++iter;
            }
        }
    
//===========================================================================================================

        // this check here is to make sure all enemies are gone before diplaying game over text

        if (enemies.empty() && !GO_Text_Active)
        {
            GO_Text_Active = true;
            done.play(); // --this is where the game over sound effect plays
            std::cout << "All Enemies have been defeated! Game Over!" << std::endl;
        }
    }

//===========================================================================================================
//  In between the clear call and the display call is where we send the render requests for our items

        // this is to clear the windows out after all items have been rendered
        newWindow.clear(sf::Color::Black); // <-- When we call clear this is also mandatory 
                                          // this is calling the clear to draw the BG???

        // small note, the order in which you draw items is reversed like the stack
        // Last one in first one out
        newWindow.draw(backGround);

        // here is mu check for the game over text
        if (!GO_Text_Active)
        {

            // this is for the bllet active on and off
            for (const auto& Bullets : myBullets)
            {
                if (Bullets.BulletActive)
                {
                    newWindow.draw(Bullets.myBullet);
                }
            }


            newWindow.draw(player);

            for (const auto& enemy : enemies)
            {
                newWindow.draw(enemy.myEnemy);
            }
        }
        else // Game is over and no longer draw
        {
            newWindow.draw(text_GameOver);
        }

//  In between the clear call and the display call is where we send the render requests for our items

//===========================================================================================================

        // this is mandatory to actually draw what all has been called per ^^^ code
        newWindow.display();  // <-- this is the command to display all rendered requests
    }

    return 0;
}