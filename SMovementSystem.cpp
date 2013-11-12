#include "SMovementSystem.h"

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
                        btTransform transform = physics->rigidBody->getWorldTransform();
                        btQuaternion rotation = transform.getRotation();

                        // create orientation vectors
                        btVector3 up(0, 1, 0);
                        btVector3 lookat = quatRotate(rotation, btVector3(0, 0, 1));
                        btVector3 forward = btVector3(lookat.getX(), 0, lookat.getZ()).normalize();
                        btVector3 side = btCross(up, forward);

                    if(input->up == true)
                    {
                        //btVector3 vec = btVector3(0,1,0);
                        //vec = vec.normalized();
                        physics->rigidBody->applyCentralImpulse(forward * 100);
                        input->up = false;

                    }
                    if(input->down == true)
                    {
                        //btVector3 vec = btVector3(0,-1,0);
                        //vec = vec.normalized();
                        physics->rigidBody->applyCentralImpulse(forward * -100);
                        input->down = false;

                    }
                    if(input->left == true)
                    {
                        //btVector3 vec = btVector3(1,0,0);
                        //vec = vec.normalized();
                        physics->rigidBody->applyCentralImpulse(side * -100);
                        input->left = false;

                    }
                    if(input->right == true)
                    {
                        //btVector3 vec = btVector3(-1,0,0);
                        //vec = vec.normalized();
                        physics->rigidBody->applyCentralImpulse(side * 100);
                        input->right = false;

                    }
                    if(input->yaw != 0 || input->pitch != 0)
                    {

                        btVector3 Amount(input->yaw * 0.001, input->pitch * 0.001, 0);
                        input->yaw = 0;
                        input->pitch = 0;

                        // rotate camera with quaternions created from axis and angle
                        rotation = btQuaternion(up,      Amount.getY()) * rotation;
                        rotation = btQuaternion(side,    Amount.getX()) * rotation;
                        //rotation = btQuaternion(forward, Amount.getZ()) * rotation;

                        // set new rotation
                        transform.setRotation(rotation);
                        //physics->rigidBody->setWorldTransform(transform);

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
