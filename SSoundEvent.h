#ifndef SSOUNDEVENT_H_INCLUDED
#define SSOUNDEVENT_H_INCLUDED

#include "entityx.h"

using namespace entityx;

struct SoundEvent : public Event<SoundEvent>
{
    Entity entity;
    SoundEvent(entityx::Entity entity) : entity(entity)
    {
    }
};

#endif // SSOUNDEVENT_H_INCLUDED
