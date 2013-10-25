#ifndef SPARTICLECOMPONENT_H_INCLUDED
#define SPARTICLECOMPONENT_H_INCLUDED

#include <lf/Lightfeather.h>
#include <entityx.h>

using namespace lf;
using namespace entityx;

struct ParticleComponent : Component<ParticleComponent>
{

    res::CParticleSystem *psys;

    ParticleComponent(std::string name)
    {
        psys = new res::CParticleSystem(name.c_str());
    }
    void addEmiter(res::CParticleEmitter *emitter)
    {
        psys->addEmitter(emitter);
    }

};


#endif // SPARTICLECOMPONENT_H_INCLUDED
