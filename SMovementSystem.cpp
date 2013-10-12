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
                    if(input->up == true)
                    {
                        btVector3 vec = btVector3(0,1,0);
                        vec = vec.normalized();
                        physics->rigidBody->applyCentralImpulse(vec * 100);
                        input->up = false;

                    }
                    if(input->down == true)
                    {
                        btVector3 vec = btVector3(0,-1,0);
                        vec = vec.normalized();
                        physics->rigidBody->applyCentralImpulse(vec * 100);
                        input->down = false;

                    }
                    if(input->left == true)
                    {
                        btVector3 vec = btVector3(1,0,0);
                        vec = vec.normalized();
                        physics->rigidBody->applyCentralImpulse(vec * 100);
                        input->left = false;

                    }
                    if(input->right == true)
                    {
                        btVector3 vec = btVector3(-1,0,0);
                        vec = vec.normalized();
                        physics->rigidBody->applyCentralImpulse(vec * 100);
                        input->right = false;

                    }
                }
                else if(model && !physics)
                {
                    if(input->up == true)
                    {
                        model->componentnode->moveUp(1.0f);
                        input->up = false;
                    }
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
