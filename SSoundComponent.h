
#pragma once

#include <entityx.h>
#include <SFML/Audio.hpp>

using namespace entityx;

struct SoundComponent : Component<SoundComponent>
{
    std::string file;
    bool playme;
    sf::Sound sound;
    sf::SoundBuffer buffer;

    SoundComponent(std::string soundfile) : file(soundfile), playme(false)
    {
            buffer.loadFromFile(file);
            sound.setBuffer(buffer);
    }
    void setSound(std::string soundfile, bool play)
    {
        playme = play;
        if(file != soundfile)
        {
            file = soundfile;
            buffer.loadFromFile(file);
            sound.setBuffer(buffer);
        }
    }
};


