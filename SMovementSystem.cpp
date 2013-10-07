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
    for (auto entity : es->entities_with_components<InputComponent, ModelComponent>())
    {

        entityx::ptr<InputComponent> inp = entity.component<InputComponent>();
        if(inp->up == true)
        {
            entityx::ptr<ModelComponent> mod = entity.component<ModelComponent>();
            mod->componentnode->moveUp(1.0f);
            inp->up = false;
        }
    }
}
