#ifndef SINPUTCOMPONENT_H_INCLUDED
#define SINPUTCOMPONENT_H_INCLUDED

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

};


#endif // SINPUTCOMPONENT_H_INCLUDED
