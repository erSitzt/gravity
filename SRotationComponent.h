#ifndef SROTATIONCOMPONENT_H_INCLUDED
#define SROTATIONCOMPONENT_H_INCLUDED

#include <lf/Lightfeather.h>
#include <btBulletDynamicsCommon.h>
#include <entityx.h>

using namespace entityx;
using namespace lf;

struct RotationComponent : Component<RotationComponent>
{

    float x,y,z,w;

    RotationComponent(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f) : x(x), y(y), z(z), w(w)
    {


    }
    RotationComponent(btQuaternion btquat)
    {
        setRotation(btquat);
    }
    RotationComponent(core::quaternion lfquat)
    {
        setRotation(lfquat);
    }
    void setRotation(core::quaternion const &lfquat)
    {
        x = lfquat.X;
        y = lfquat.Y;
        z = lfquat.Z;
        w = lfquat.W;
    }
    void setRotation(btQuaternion const &btquat )
    {
        x = btquat.x();
        y = btquat.y();
        z = btquat.z();
        w = btquat.w();
    }
    core::quaternion getRotationLF()
    {
        return core::quaternion(x,y,z,w);
    }
    btQuaternion getRotationBT()
    {
        return btQuaternion(x,y,z,w);
    }


};

#endif // SROTATIONCOMPONENT_H_INCLUDED
