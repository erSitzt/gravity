#ifndef CPHYSICSSYSTEM_H
#define CPHYSICSSYSTEM_H

#include <btBulletDynamicsCommon.h>
#include "entityx.h"
#include "events.h"
#include "components.h"

using namespace entityx;

struct CPhysicsSystem : public System<CPhysicsSystem>, Receiver<CPhysicsSystem>
{
public:
    btDiscreteDynamicsWorld* dynamicsWorld;
    EntityManager *emptr;
    EventManager *evptr;
    entityx::ptr<EventManager> events;

    CPhysicsSystem(entityx::ptr<EntityManager> em);
    virtual ~CPhysicsSystem();
    void configure(entityx::ptr<EventManager> event_manager);

    // Notifications if PhysicsComponents are added to an entity
    void receive(const ComponentAddedEvent<PhysicsGhostComponent> &physicscomponent);
    void receive(const ComponentAddedEvent<PhysicsComponent> &physicscomponent);

    // Called by main-loop
    void update(entityx::ptr<EntityManager> es, entityx::ptr<EventManager> events, double dt) override;

    void checkGhostCollision();
    void processGhostCollisions(btAlignedObjectArray<btCollisionObject*>& obj, btGhostObject *ghost);
    static bool contactCallbackFunction(btManifoldPoint& cp,const btCollisionObjectWrapper* obj1,int id0,int index0,const btCollisionObjectWrapper* obj2,int id1,int index1);

};

struct BulletCallbackHelper
{
    entityx::Entity::Id entityid;
    EntityManager *entitymanager;
    EventManager *eventmanager;

    BulletCallbackHelper(Entity::Id entityid, EntityManager *entitymanager, EventManager *eventmanager) : entityid(entityid), entitymanager(entitymanager), eventmanager(eventmanager)
    {
        //ctor
    }
};

#endif // CPHYSICSSYSTEM_H
