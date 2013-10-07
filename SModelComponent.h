#ifndef SMODELCOMPONENT_H_INCLUDED
#define SMODELCOMPONENT_H_INCLUDED

#include <lf/Lightfeather.h>
#include "entityx.h"
#include "events.h"

using namespace lf;
using namespace entityx;

struct ModelComponent : Component<ModelComponent>
{

    scene::CModelSceneNode *componentnode;

    ModelComponent(res::CModel *model)
    {
        componentnode = new scene::CModelSceneNode(model);
    }

};

#endif // SMODELCOMPONENT_H_INCLUDED

