#ifndef SWEAPONSYSTEM_H
#define SWEAPONSYSTEM_H

#include "entityx.h"
#include "events.h"
#include "components.h"

using namespace entityx;

struct SWeaponSystem : public System<SWeaponSystem>, Receiver<SWeaponSystem>
{
    public:
        SWeaponSystem();
        virtual ~SWeaponSystem();
        void configure(entityx::ptr<EventManager> event_manager);
        void update(entityx::ptr<EntityManager> es, entityx::ptr<EventManager> events, double dt);
        void receive(const WeaponEvent &weapon);

};

#endif // SWEAPONSYSTEM_H
