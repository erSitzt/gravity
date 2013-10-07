#ifndef CPHYSICSSYSTEM_H
#define CPHYSICSSYSTEM_H

#include <btBulletDynamicsCommon.h>
#include "entityx.h"
#include "events.h"
#include "components.h".h"

using namespace entityx;

struct CPhysicsSystem : public System<CPhysicsSystem>, Receiver<CPhysicsSystem>
{
    public:
        btDiscreteDynamicsWorld* dynamicsWorld;

        CPhysicsSystem();
        virtual ~CPhysicsSystem();
        void configure(entityx::ptr<EventManager> event_manager);

        // Notifications if PhysicsComponents are added to an entity
        void receive(const ComponentAddedEvent<PhysicsGhostComponent> &physicscomponent);
        void receive(const ComponentAddedEvent<PhysicsComponent> &physicscomponent);

        // Called by main-loop
        void update(entityx::ptr<EntityManager> es, entityx::ptr<EventManager> events, double dt) override;

        void checkGhostCollision();
        void processGhostCollisions(btAlignedObjectArray<btCollisionObject*>& obj, btGhostObject *ghost);

};

#endif // CPHYSICSSYSTEM_H
