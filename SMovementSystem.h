#ifndef SMOVEMENTSYSTEM_H
#define SMOVEMENTSYSTEM_H

#include <lf/Lightfeather.h>
#include "util.h"
#include "entityx.h"
#include "events.h"
#include "components.h"

using namespace lf;
using namespace entityx;

struct SMovementSystem : public System<SMovementSystem>, Receiver<SMovementSystem>
{
public:
    entityx::ptr<EventManager> events;

    SMovementSystem();
    virtual ~SMovementSystem();
    void configure(entityx::ptr<EventManager> event_manager);
    void update(entityx::ptr<EntityManager> es, entityx::ptr<EventManager> events, double dt);
    btVector3 GetForwardVector(btQuaternion q) const;
    btVector3 GetUpVector(btQuaternion q) const;
    btVector3 GetRightVector(btQuaternion q) const;

};

#endif // SMOVEMENTSYSTEM_H
