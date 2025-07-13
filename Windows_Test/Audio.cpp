#include "Audio.h"
#include <iostream>
#include <map>

Audio::Audio()
{
    //  this is for my constructor
}

    //  This is where I load music and sound effexts to be played in game
bool Audio::loadMusic(const std::string &fileName)
{
    if (!gameMusic.openFromFile(fileName))
    {
        std::cout << "Error loading music: " << fileName << std::endl;
        return false;
    }
    return true;
}

void Audio::playMusic()
{
    gameMusic.play();
}

void Audio::stopMusic()
{
    gameMusic.stop();
}

void Audio::setMusicLoop(bool loop)
{ 
    gameMusic.setLoop(loop);
}

bool Audio::loadSoundEffect(const std::string& filename, const std::string& effectName) {

    // this is to load the sound effects to be used
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filename)) {
        std::cerr << "Error loading sound effect: " << filename << std::endl;
        return false;
    }
    soundBuffers[effectName] = buffer;
    soundEffects[effectName].setBuffer(soundBuffers[effectName]);
    return true;
}

sf::Sound& Audio::getSoundEffect(const std::string& effectName) {
    return soundEffects.at(effectName);
}