#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Audio.h"
#include "MainMenu.h"

class myApp
{
public:
    myApp();
    void runMe();

private:  
    //  Game States are here now
    enum class GameState
    {
        MainMenu,
        Playing,
        GameOver
    };
    
    //  variables for the game go here
    sf::RenderWindow newWindow;
    sf::Clock myClock;
    //bool goTextActive = false;
    float bulletSpeed = 200.f;
    MainMenu myMainMenu;

    //  Game Objects here
    Player myPlayer;
    Audio myAudio;
    std::vector<Enemy> enemies;
    std::vector<Bullet> bullets;

    //  Set my Game State
    GameState currentState;

    //  SFML assets
    sf::Sprite backGround;
    sf::Text textGameOver;
    sf::Font fontGameOver;
    sf::Texture textureBackground;
    sf::Texture enemyShipTexture;

    //  Helper methods for loading and intiailizing enemies
    void loadAssets();
    void initializeEnemies(int count);
    void handleEvents();
    void updateLogic(float deltaTime);
    void render();

};