#include "App.h"
#include <iostream>
#include <filesystem>

int main()
{
    std::cout << "This is my CWD: " << std::filesystem::current_path() << std::endl;

    myApp game;
    game.runMe();
    return 0;
}