#include "CDebuggingSystem.h"

CDebuggingSystem::CDebuggingSystem()
{
    //ctor
}

CDebuggingSystem::~CDebuggingSystem()
{
    //dtor
}
void CDebuggingSystem::configure(entityx::ptr<EventManager> event_manager)
{
}
void CDebuggingSystem::update(entityx::ptr<EntityManager> es, entityx::ptr<EventManager> events, double dt)
{
    for (auto entity : es->entities_with_components<PositionComponent, RotationComponent>())
    {
        entityx::ptr<PositionComponent> position = entity.component<PositionComponent>();
        entityx::ptr<RotationComponent> rotation = entity.component<RotationComponent>();


        // Do things with entity, position and direction.
    }
}
