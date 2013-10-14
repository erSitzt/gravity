#ifndef SLISTENERPOSITIONCHANGEDEVENT_H_INCLUDED
#define SLISTENERPOSITIONCHANGEDEVENT_H_INCLUDED

#include <lf/Lightfeather.h>
#include "entityx.h"

using namespace entityx;
using namespace lf;

struct ListenerPositionChangedEvent : public Event<ListenerPositionChangedEvent>
{
    core::vector3df pos;
    ListenerPositionChangedEvent(core::vector3df pos) : pos(pos)
    {
    }
};

#endif // SLISTENERPOSITIONCHANGEDEVENT_H_INCLUDED
