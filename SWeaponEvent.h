#ifndef SWEAPONEVENT_H_INCLUDED
#define SWEAPONEVENT_H_INCLUDED

#include "entityx.h"

using namespace entityx;

struct WeaponEvent : public Event<WeaponEvent>
{
    WeaponEvent()
    {
    }
};


#endif // SWEAPONEVENT_H_INCLUDED
