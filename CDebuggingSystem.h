#ifndef CDEBUGGINGSYSTEM_H
#define CDEBUGGINGSYSTEM_H

#include <btBulletDynamicsCommon.h>
#include "entityx.h"
#include "events.h"
#include "components.h".h"

using namespace entityx;

struct CDebuggingSystem : public System<CDebuggingSystem>, Receiver<CDebuggingSystem>
{
public:
    CDebuggingSystem();
    virtual ~CDebuggingSystem();
    void configure(entityx::ptr<EventManager> event_manager);
    void update(entityx::ptr<EntityManager> es, entityx::ptr<EventManager> events, double dt) override;


};

#endif // CDEBUGGINGSYSTEM_H
