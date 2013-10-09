#ifndef SSOUNDSYSTEM_H
#define SSOUNDSYSTEM_H


#include "entityx.h"
#include "events.h"
#include "SSoundComponent.h"


using namespace entityx;

struct SSoundSystem : public System<SSoundSystem>, Receiver<SSoundSystem>
{
    public:
        SSoundSystem();
        virtual ~SSoundSystem();
        void configure(entityx::ptr<EventManager> event_manager);
        void update(entityx::ptr<EntityManager> es, entityx::ptr<EventManager> events, double dt);

};

#endif // SSOUNDSYSTEM_H
