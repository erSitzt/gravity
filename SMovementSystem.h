#ifndef SMOVEMENTSYSTEM_H
#define SMOVEMENTSYSTEM_H

#include <lf/Lightfeather.h>
#include "entityx.h"
#include "events.h"
#include "components.h"

using namespace lf;
using namespace entityx;

struct SMovementSystem : public System<SMovementSystem>, Receiver<SMovementSystem>
{
    public:
        SMovementSystem();
        virtual ~SMovementSystem();
    void configure(entityx::ptr<EventManager> event_manager);
    void update(entityx::ptr<EntityManager> es, entityx::ptr<EventManager> events, double dt);

};

#endif // SMOVEMENTSYSTEM_H
