#include "SMovementSystem.h"

using namespace lf;

SMovementSystem::SMovementSystem()
{
    //ctor
}

SMovementSystem::~SMovementSystem()
{
    //dtor
}
void SMovementSystem::configure(entityx::ptr<EventManager> event_manager)
{
    events = event_manager;
}
void SMovementSystem::update(entityx::ptr<EntityManager> es, entityx::ptr<EventManager> events, double dt)
{
    for (auto entity : es->entities_with_components<PositionComponent>())
    {

        entityx::ptr<PositionComponent> pos = entity.component<PositionComponent>();
        if(pos)
        {
            entityx::ptr<InputComponent> input = entity.component<InputComponent>();
            if(input)
            {
                entityx::ptr<ModelComponent> model = entity.component<ModelComponent>();
                entityx::ptr<PhysicsComponent> physics = entity.component<PhysicsComponent>();
                entityx::ptr<PhysicsGhostComponent> ghost = entity.component<PhysicsGhostComponent>();
                if(model && physics)
                {
                    btTransform transform;
                    physics->rigidBody->getMotionState()->getWorldTransform(transform);
                    btQuaternion rotation = transform.getRotation();
                    core::quaternion lfrot = gravutil::getLFQuatFromBT(rotation);

                    // create orientation vectors
//                    btVector3 up(0, 1, 0);
//                    btVector3 lookat = quatRotate(rotation, btVector3(0, 0, 1));
//                    btVector3 forward = btVector3(lookat.getX(), 0, lookat.getZ()).normalize();
//                    btVector3 side = btCross(up, forward);

                    core::vector3df lfup = lfrot * core::vector3df(0, 1, 0);
                    core::vector3df lfforward = lfrot * core::vector3df(0, 0, 1);
                    core::vector3df lfside = lfrot * core::vector3df(1, 0, 0);
                    btVector3 up = gravutil::getBTVecFromLF(lfup);
                    btVector3 forward = gravutil::getBTVecFromLF(lfforward);
                    btVector3 side = gravutil::getBTVecFromLF(lfside);



                    if(!input->shift)
                    {
                        if(input->up == true)
                        {
                            physics->rigidBody->applyCentralImpulse(forward * 100);
                            input->up = false;
                        }
                        if(input->down == true)
                        {
                            physics->rigidBody->applyCentralImpulse(forward * -100);
                            input->down = false;
                        }
                    }
                    else
                    {
                        if(input->up == true)
                        {
                            physics->rigidBody->applyCentralImpulse(up * 100);
                            input->up = false;
                        }
                        if(input->down == true)
                        {
                            physics->rigidBody->applyCentralImpulse(up * -100);
                            input->down = false;
                        }
                    }
                    if(input->left == true)
                    {
                        physics->rigidBody->applyCentralImpulse(side * -100);
                        input->left = false;
                    }
                    if(input->right == true)
                    {
                        physics->rigidBody->applyCentralImpulse(side * 100);
                        input->right = false;
                    }
                    if(input->yaw != 0 || input->pitch != 0)
                    {
                        std::cout << "Yaw : " << input->yaw << " Pitch : " << input->pitch << " DT : " << dt << std::endl;
                        btVector3 Amount(input->yaw * dt, input->pitch * dt, 0);
                        input->yaw = 0;
                        input->pitch = 0;

                        // rotate camera with quaternions created from axis and angle
                        //rotation.setRotation(up, 10);
                        rotation = btQuaternion(up,      Amount.getX()) * rotation;
                        rotation = btQuaternion(side,    Amount.getY()) * rotation;
//                        rotation = btQuaternion(forward, Amount.getZ()) * rotation;

                        // set new rotation
                        std::cout << "Yaw : " << input->yaw << " Pitch : " << input->pitch << std::endl;
                        std::cout << "Rot. Angle : " << rotation.getAngle() << std::endl;
                        std::cout << "Rot.  X : " << rotation.getX() << " Rot. X : " << rotation.getY() << " Rot. X : " << rotation.getZ() << std::endl;
                        std::cout << "UP.   X : " << up.getX() << " UP.   X : " << up.getY() << " UP.   X : " << up.getZ() << std::endl;
                        std::cout << "FWD.  X : " << forward.getX() << " FWD.  X : " << forward.getY() << " FWD.  X : " << forward.getZ() << std::endl;
                        std::cout << "SIDE. X : " << side.getX() << " SIDE. X : " << side.getY() << " SIDE. X : " << side.getZ() << std::endl;
                        transform.setRotation(rotation);

                        physics->rigidBody->setWorldTransform(transform);


                    }
                }
                else if(model && !physics)
                {
                    if(input->up == true)
                    {
                        pos->y += 1.0f;
                    }
                    if(input->down == true)
                    {
                        pos->y -= 1.0f;
                    }
                    if(input->left == true)
                    {
                        pos->z += 1.0f;
                    }
                    if(input->right == true)
                    {
                        pos->z -= 1.0f;
                    }

                    this->events->emit<PositionChangedEvent>(entity);
                }
                else
                {
                    if(input->up == true)
                    {
                        btVector3 vec = btVector3(0,1,0);
                        vec = vec.normalized();
                        physics->rigidBody->applyCentralImpulse(vec * 100);
                        input->up = false;

                    }
                }

            }
        }
    }
}

btVector3 SMovementSystem::GetForwardVector(btQuaternion q) const
{
    btScalar x = q.x();
    btScalar y = q.y();
    btScalar z = q.z();
    btScalar w = q.w();
    return btVector3( 2 * (x * z + w * y),
                    2 * (y * x - w * x),
                    1 - 2 * (x * x + y * y));
}

btVector3 SMovementSystem::GetUpVector(btQuaternion q) const
{
    btScalar x = q.x();
    btScalar y = q.y();
    btScalar z = q.z();
    btScalar w = q.w();
    return btVector3( 2 * (x * y - w * z),
                    1 - 2 * (x * x + z * z),
                    2 * (y * z + w * x));
}

btVector3 SMovementSystem::GetRightVector(btQuaternion q) const
{
    btScalar x = q.x();
    btScalar y = q.y();
    btScalar z = q.z();
    btScalar w = q.w();
    return btVector3( 1 - 2 * (y * y + z * z),
                    2 * (x * y + w * z),
                    2 * (x * z - w * y));
}

/*
    for (auto entity : es->entities_with_components<InputComponent, PhysicsGhostComponent>())
    {

        entityx::ptr<InputComponent> inp = entity.component<InputComponent>();
        if(inp->up == true)
        {
            entityx::ptr<PhysicsGhostComponent> gho = entity.component<PhysicsGhostComponent>();
            btVector3 upDir = gho->ghost->getWorldTransform().getBasis()[1];
            upDir.normalize();
            btVector3 oldpos = gho->ghost->getWorldTransform().getOrigin();
            gho->ghost->getWorldTransform().setOrigin(oldpos + upDir);

            inp->up = false;
        }
    }
    */
