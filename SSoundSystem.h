#ifndef SSOUNDSYSTEM_H
#define SSOUNDSYSTEM_H


#include <lf/Lightfeather.h>
#include "entityx.h"
#include "events.h"
#include "components.h"


using namespace entityx;

struct SSoundSystem : public System<SSoundSystem>, Receiver<SSoundSystem>
{
    public:
        SSoundSystem();
        virtual ~SSoundSystem();
        void configure(entityx::ptr<EventManager> event_manager);
        void update(entityx::ptr<EntityManager> es, entityx::ptr<EventManager> events, double dt);
        void receive(const ListenerPositionChangedEvent &listenerposchange);
        static void setListenerPosition(core::vector3df pos);

};

#endif // SSOUNDSYSTEM_H
