#ifndef SPHYSICSCOMPONENT_H_INCLUDED
#define SPHYSICSCOMPONENT_H_INCLUDED

#include <btBulletDynamicsCommon.h>

#include <entityx.h>

using namespace entityx;

struct PhysicsComponent : Component<PhysicsComponent>
{

    btCollisionShape *shape;
    btScalar mass;
    btRigidBody *rigidBody;
    btMotionState *motionState;
    btVector3 fallInertia;

    PhysicsComponent(btCollisionShape *shape, btMotionState *motionState, btScalar mass, btVector3 fallInertia) : shape(shape), motionState(motionState), mass(mass), fallInertia(fallInertia)
    {
        shape->calculateLocalInertia(mass, fallInertia);
        btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass,motionState,shape,fallInertia);
        rigidBody = new btRigidBody(rigidBodyCI);
        rigidBody->setActivationState(DISABLE_DEACTIVATION);

    }

};

#endif // SPHYSICSCOMPONENT_H_INCLUDED





