#ifndef SPOSITIONCOMPONENT_H_INCLUDED
#define SPOSITIONCOMPONENT_H_INCLUDED

#include <lf/Lightfeather.h>
#include <btBulletDynamicsCommon.h>
#include <entityx.h>

using namespace entityx;
using namespace lf;

struct PositionComponent : Component<PositionComponent>
{

    float x,y,z;

    PositionComponent(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z)
    {


    }
    PositionComponent(btVector3 btpos)
    {
        setPosition(btpos);
    }
    PositionComponent(core::vector3df lfpos)
    {
        setPosition(lfpos);
    }
    void setPosition(core::vector3df const &lfvector)
    {
        x = lfvector.X;
        y = lfvector.Y;
        z = lfvector.Z;
    }
    void setPosition(btVector3 const &btvector )
    {
        x = btvector.x();
        y = btvector.y();
        z = btvector.z();

    }
    core::vector3df getPositionLF()
    {
        return core::vector3df(x,y,z);
    }
    btVector3 getPositionBT()
    {
        return btVector3(x,y,z);
    }

};

#endif // SPOSITIONCOMPONENT_H_INCLUDED
