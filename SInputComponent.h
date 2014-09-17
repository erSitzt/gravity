#ifndef SINPUTCOMPONENT_H_INCLUDED
#define SINPUTCOMPONENT_H_INCLUDED

#include "entityx.h"
#include <cereal/archives/json.hpp>
#include <fstream>

using namespace lf;
using namespace entityx;

struct InputComponent : Component<InputComponent>
{

    bool left;
    bool right;
    bool up;
    bool down;
    bool shift;
    f32 yaw;
    f32 pitch;
    f32 roll;

    input::EKEY_CODE key;

    InputComponent()
    {

    }
    template<class Archive>
    void save(Archive & archive) const
    {
        archive(
            CEREAL_NVP(left),
            CEREAL_NVP(right),
            CEREAL_NVP(up),
            CEREAL_NVP(down),
            CEREAL_NVP(yaw),
            CEREAL_NVP(pitch),
            CEREAL_NVP(roll)
            );
    }

};

#endif // SINPUTCOMPONENT_H_INCLUDED
