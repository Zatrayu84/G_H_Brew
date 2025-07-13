#pragma once

#include <SFML/Audio.hpp>
#include <string>
#include <map> // this is new for me, std::map


class Audio
{
public:
    Audio();

    bool loadMusic(const std::string &fileName);
    void playMusic();
    void stopMusic();
    void setMusicLoop(bool loop);

    bool loadSoundEffect(const std::string & fileName, const std::string & effectName);
    sf::Sound & getSoundEffect(const std::string & effectName);

private:

    //  use this instead of just load music allowing me to play and stop music as needed
    sf::Music gameMusic;
    std::map<std::string, sf::SoundBuffer> soundBuffers;
    std::map<std::string, sf::Sound> soundEffects;
};