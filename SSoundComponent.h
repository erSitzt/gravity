
#pragma once

#include <entityx.h>
#include <SFML/Audio.hpp>

using namespace entityx;

struct SoundComponent : Component<SoundComponent>
{
    std::string file;
    bool playme;
    bool loop;
    float pitch;
    float attenuation;
    float volume;
    sf::Sound sound;
    sf::SoundBuffer buffer;

    SoundComponent(std::string soundfile) : file(soundfile), playme(false), loop(false), pitch(1.0), attenuation(1.0), volume(100.0)
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
            sound.setVolume(volume);
            sound.setAttenuation(attenuation);
            sound.setLoop(loop);
            sound.setPitch(pitch);
        }
    }
};


