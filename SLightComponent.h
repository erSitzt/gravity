#ifndef SLIGHTCOMPONENT_H_INCLUDED
#define SLIGHTCOMPONENT_H_INCLUDED

#include <lf/Lightfeather.h>
#include <entityx.h>

using namespace lf;
using namespace entityx;

struct LightComponent : Component<LightComponent>
{

    scene::CLight *light;

    LightComponent(core::CColorF color = core::CColorF(0.4f, 0.0f, 0.0f, 1.0f))
    {
        light = new scene::CLight(color);
    }
};
#endif // SLIGHTCOMPONENT_H_INCLUDED



