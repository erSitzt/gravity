#ifndef SPOSITIONCHANGEDEVENT_H_INCLUDED
#define SPOSITIONCHANGEDEVENT_H_INCLUDED

#include <btBulletDynamicsCommon.h>
#include "entityx.h"

using namespace entityx;

struct PositionChangedEvent : public Event<PositionChangedEvent>
{
    Entity entity;
    PositionChangedEvent(entityx::Entity entity) : entity(entity)
    {
    }
};

#endif // SPOSITIONCHANGEDEVENT_H_INCLUDED
