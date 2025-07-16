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
    //sf::SoundBuffer buffer;

    // --- ATTEMPTING TO FIX -  DEBUGGING CODE ---
    std::cout << "Attempting to load sound effect: " << filename << " with key: " << effectName << std::endl;
    // --- END DEBUGGING CODE ---

    if (!soundBuffers[effectName].loadFromFile(filename))
    {

    // --- ATTEMPTING TO FIX -  DEBUGGING CODE ---
        std::cerr << "SFML failed to load sound effect from: " << filename << std::endl;
        std::cerr << "Ensure file exists and path is correct relative to CWD." << std::endl;
        // --- END DEBUGGING CODE ---

        soundBuffers.erase(effectName); // this is to verify that there is no ghost data...
        return false;
    }
    soundEffects[effectName].setBuffer(soundBuffers[effectName]);

     // --- ADD THIS DEBUGGING CODE ---
    std::cout << "Successfully loaded sound effect: " << filename << " with key: " << effectName << std::endl;
    // --- END DEBUGGING CODE ---
    
    return true;
}

sf::Sound& Audio::getSoundEffect(const std::string& effectName) {
    return soundEffects.at(effectName);
}