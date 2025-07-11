#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Audio.h"

class myApp
{
public:
    myApp();
    void runMe();

private:  
    //  variables for the game go here
    sf::RenderWindow newWindow;
    sf::Clock myClock;
    bool goTextActive = false;
    float bulletSpeed = 200.f;

    //  Game Objects here
    Player myPlayer;
    Audio myAudio;
    std::vector<Enemy> enemies;
    std::vector<Bullets> bullets;

    //  SFML assets
    sf::Sprite background;
    sf::Text textGameOver;
    sf::Font fontGameOver;
    sf::Texture texture;

    //  Helper methods for loading and intiailizing enemies
    void loadAssets();
    void initializeEnemies();
    void handleEvents();
    void updateLogic(float deltaTime);
    void render();

};