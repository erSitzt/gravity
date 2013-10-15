#ifndef SCAMERACOMPONENT_H_INCLUDED
#define SCAMERACOMPONENT_H_INCLUDED

#include <lf/Lightfeather.h>
#include <entityx.h>

using namespace lf;
using namespace entityx;

struct CameraComponent : Component<CameraComponent>
{

    scene::C3DCamera cam;
    CameraComponent()
    {

    }

};

#endif // SCAMERACOMPONENT_H_INCLUDED
