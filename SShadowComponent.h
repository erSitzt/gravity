#ifndef SSHADOWCOMPONENT_H_INCLUDED
#define SSHADOWCOMPONENT_H_INCLUDED

using namespace lf;
using namespace entityx;

struct ShadowComponent : Component<ShadowComponent>
{

    bool castShadows;
    bool receiveShadows;

    ShadowComponent(bool cast, bool receive) : castShadows(cast), receiveShadows(receive)
    {

    }
};

#endif // SSHADOWCOMPONENT_H_INCLUDED
