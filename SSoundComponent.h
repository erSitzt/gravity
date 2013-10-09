
#pragma once

#include <entityx.h>


using namespace entityx;

struct SoundComponent : Component<SoundComponent>
{
    std::string file;

    //sf::Sound sound;
    //sf::SoundBuffer buffer;

    SoundComponent(const std::string soundfile) : file(soundfile)
    {
        //buffer.loadFromFile(file);
        //sound.setBuffer(buffer);
    }
};


