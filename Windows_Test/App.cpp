#include "App.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <sstream>

// Helper function to split with delimeter
std::vector<std::string> splitString(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

    //  Constructor here
myApp::myApp() : newWindow(sf::VideoMode(800, 800), "Galaga_HomeBrew - Erik Segura"), myMainMenu(800,800), currentState(GameState::MainMenu)
{
    newWindow.setPosition(sf::Vector2i(200, 125));
    loadAssets();
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

    std::string gameOverString = "YOU WIN! \n Press R to Restart \n Hit ESC to return to Main menu";
    std::vector<std::string> lines = splitString(gameOverString, '\n');

    float charSize = 30.0f; // Character size for all lines
    float lineHeight = charSize + 10.0f; // Approximate line height + padding

    // Calculate total height of the text block for vertical centering
    float totalTextHeight = lines.size() * lineHeight;

    // Calculate the Y position for the very top of the centered text block
    float startY = (newWindow.getSize().y / 2.0f) - (totalTextHeight / 2.0f);

    for (size_t i = 0; i < lines.size(); ++i)
    {
        sf::Text lineText;
        lineText.setFont(fontGameOver);
        lineText.setString(lines[i]);
        lineText.setCharacterSize(static_cast<unsigned int>(charSize));
        lineText.setFillColor(sf::Color::Red);
        lineText.setStyle(sf::Text::Bold);

        // Set origin to the center of THIS line's bounds
        sf::FloatRect textBounds = lineText.getLocalBounds();
        lineText.setOrigin(textBounds.left + textBounds.width / 2.0f,
                           textBounds.top + textBounds.height / 2.0f);

        // Position this line horizontally centered and vertically stacked
        lineText.setPosition(newWindow.getSize().x / 2.0f,
                             startY + (i * lineHeight) + (lineHeight / 2.0f)); // Add lineHeight/2.0f to center the line within its allocated vertical space

        gameOverLines.push_back(lineText);
    }

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
    
    if (!logoTexture.loadFromFile("Sprites/Galaga_Logo.png"))
    {
        std::cout << "Error loading texture file: Sprites/Galaga_Logo.png" << std::endl;
    }

    menuLogo.setTexture(logoTexture);
    menuLogo.setScale(.5f, .5f);
    sf::FloatRect logoBounds = menuLogo.getLocalBounds();
    menuLogo.setOrigin(logoBounds.left + logoBounds.width / 2.0f, logoBounds.top + logoBounds.height / 2.0f);
    menuLogo.setPosition(newWindow.getSize().x / 2.0f, newWindow.getSize().y / 4.0f);
    myPlayer.draw(newWindow);
}

void myApp::initializeEnemies(int count)
{
    float enemyWidth = 50.f;
    float enemyHeight = 50.f;
    
    enemies.clear();
    // Parameters for the rows
    const float enemySpacingX = enemyWidth + 10.0f;
    const float enemySpacingY = enemyHeight;

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
            newWindow.close();
            std::cout << "This is now closed" << std::endl;
        }

        // Handle input based on current game state
        if (event.type == sf::Event::KeyPressed)
        {
            //  Here are where the game states are deermined
            if (currentState == GameState::MainMenu)
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    myMainMenu.moveUp();
                }
                if (event.key.code == sf::Keyboard::Down)
                {
                    myMainMenu.movedown();
                }
                if (event.key.code == sf::Keyboard::Enter)
                {
                    int selectedItem = myMainMenu.MainMenuPressed();
                    if (selectedItem == 0) // Play
                    {
                        currentState = GameState::Playing;
                        initializeEnemies(enemyDef); // Start the game by initializing enemies
                        bullets.clear();
                        enemyBullets.clear();
                        //myPlayer.reset(); // Reset player position for a new game
                    }
                    else if (selectedItem == 1) // Options - implement later 
                    {
                        std::cout << "Options selected!" << std::endl;
                    }
                    else if (selectedItem == 2) // About - implement later 
                    {
                        std::cout << "About selected!" << std::endl;
                    }
                    else if (selectedItem == 3) // Exit
                    {
                        newWindow.close();
                        std::cout << "Exiting from menu." << std::endl;
                    }
                }
            }
            else if (currentState == GameState::Playing) {
                if (event.key.code == sf::Keyboard::Space)
                {
                    myPlayer.shoot(bullets, myAudio.getSoundEffect("pew"));
                }
                else if (event.key.code == sf::Keyboard::Escape) // Back to main menu on 'Escape'
                {
                    currentState = GameState::MainMenu;
                    // reset game elements here if going back to menu
                    enemies.clear();
                    bullets.clear();
                    enemyBullets.clear();
                    //myPlayer.reset();
                }
            }
            else if (currentState == GameState::GameOver)
            {
                if (event.key.code == sf::Keyboard::R) // Restart on 'R' key
                {
                    currentState = GameState::Playing;
                    initializeEnemies(enemyDef);
                    bullets.clear();
                    enemyBullets.clear();
                    myAudio.playMusic();
                    // myPlayer.reset();
                }
                else if (event.key.code == sf::Keyboard::Escape) // Back to main menu on 'Escape'
                {
                    currentState = GameState::MainMenu;
                    // You might want to reset game elements here if going back to menu
                    enemies.clear();
                    bullets.clear();
                    enemyBullets.clear();
                    myAudio.playMusic();
                    //myPlayer.reset(); // Or place player off-screen
                }
            }
        }
    }
    if (currentState == GameState::Playing)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            myPlayer.move(-1.0f, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            myPlayer.move(1.0f, 0.0f);
        }
    }
}

void myApp::updateLogic(float deltaTime)
{
    if (currentState == GameState::Playing)
    {
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
            if (enemies.empty())
            {
                currentState = GameState::GameOver;
                myAudio.getSoundEffect("done").play();
                myAudio.stopMusic();
                std::cout << "Game Over, all enemies have been destroyed" << std::endl; // this is for terminal output
           }
        }

        sf::Vector2f playerPos = myPlayer.getPosition(); // Get the current player position
        for (auto& enemy : enemies)
        {
            // The enemy must have the canShoot() and updated shoot(...) methods implemented
            if (enemy.canShoot())
            {
                // Note: The shoot() function must now accept the target position (playerPos)
                enemy.shoot(enemyBullets, myAudio.getSoundEffect("pew"), playerPos);
            }
        }

        // this is the iterator to check my collisions
        for (auto enemyBulletIter = enemyBullets.begin(); enemyBulletIter != enemyBullets.end();)
        {
            enemyBulletIter->update(deltaTime);

            // Check for Player Collision OR if bullet is off-screen/inactive
            if (!enemyBulletIter->isActive() ||
                enemyBulletIter->getGlobalBounds().intersects(myPlayer.getGlobalBounds()))
            {
                // Check if edge of area was reached
                if (enemyBulletIter->getGlobalBounds().intersects(myPlayer.getGlobalBounds()))
                {
                    std::cout << "Player HIT by enemy bullet!" << std::endl;
                    myAudio.getSoundEffect("boom").play(); // Use the explosion sound
                }

                // Remove the bullet from the vector
                enemyBulletIter = enemyBullets.erase(enemyBulletIter);
            }
            else
            {
                // No collision and bullet is still active, move to the next bullet
                ++enemyBulletIter;
            }
        }
        //  Eventually add logic to handle player lives, and score reset.
    }
}

void myApp::render()
{
        newWindow.clear(sf::Color::Black); 
        newWindow.setView(newWindow.getDefaultView());
        newWindow.draw(backGround);

        // here is mu check for the game over text
        if (currentState == GameState::MainMenu)
        {
            newWindow.draw(menuLogo);
            myMainMenu.draw(newWindow);
        }
        else if (currentState == GameState::Playing)
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
            for (auto& bullet : enemyBullets)
            {
                bullet.draw(newWindow);
            }
        }
        else if(currentState == GameState::GameOver)
        {
            for (const auto& line : gameOverLines)
        {
            newWindow.draw(line);
        }
        }
        newWindow.display();
}




