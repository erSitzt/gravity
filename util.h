#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include <lf/Lightfeather.h>
#include <btBulletDynamicsCommon.h>

using namespace lf;

namespace gravutil
{
inline btVector3 getBTVecFromLF(const core::vector3df& lfvec)
{
    return btVector3(lfvec.X, lfvec.Y, lfvec.Z);
}
inline core::vector3df getLFVecFromBT(const btVector3& btvec)
{
    return core::vector3df(btvec.getX(), btvec.getY(), btvec.getZ());
}
inline core::quaternion getLFQuatFromBT(const btQuaternion& btquat)
{
    return core::quaternion(btquat.getX(), btquat.getY(), btquat.getZ(), btquat.getW());
}
inline btQuaternion getBTQuatFromLF(const core::quaternion& lfquat)
{
    return btQuaternion(lfquat.X, lfquat.Y, lfquat.Z, lfquat.W );
}

}
#endif // UTIL_H_INCLUDED
