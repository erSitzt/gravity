#include "CPhysicsSystem.h"
extern ContactAddedCallback gContactAddedCallback;

CPhysicsSystem::CPhysicsSystem(entityx::ptr<entityx::EntityManager> em)
{
    //ctor
    entityx::EntityManager * hans = (entityx::EntityManager*)em.get();
    emptr = hans;
}

CPhysicsSystem::~CPhysicsSystem()
{
    //dtor
}
bool CPhysicsSystem::contactCallbackFunction(btManifoldPoint& cp,const btCollisionObjectWrapper* obj1,int id0,int index0,const btCollisionObjectWrapper* obj2,int id1,int index1)
{
    //std::cout << "collision" << std::endl;
    static_assert(sizeof(void*) == sizeof(uint64_t), "need 64 bit pointers");
    /** TODO (ersitzt#1#12.10.2013): Handle collision events, as soon as UserPointer with Bullet works */
    // alec
    //Entity::Id id(reinterpret_cast<uint64_t>(obj1->getCollisionObject()->getUserPointer()));
    BulletCallbackHelper *helper = reinterpret_cast<BulletCallbackHelper*>(obj1->getCollisionObject()->getUserPointer());

    //EntityManager *tetete = ((EntityManager*)helper->entitymanager);
    entityx::EntityManager *tetete = (entityx::EntityManager*)(helper->entitymanager);

    entityx::Entity ent = tetete->get(helper->entityid);

    entityx::ptr<SoundComponent> sound = ent.component<SoundComponent>();
    if(sound)
    {
        std::string snd = "/home/ersitzt/impact.wav";
        sound->setSound(snd, true);
    }
}

void CPhysicsSystem::configure(entityx::ptr<EventManager> event_manager)
{
    std::cout << "CPhysicsSystem configure" << std::endl;

    //Setup Bullet Physics
    btBroadphaseInterface* broadphase = new btDbvtBroadphase();
    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0,0,0));
    // Ghost-Objects
    btGhostPairCallback *ghostCall = new btGhostPairCallback();
    dynamicsWorld->getBroadphase()->getOverlappingPairCache()->setInternalGhostPairCallback(ghostCall);
    // Collision callback
    gContactAddedCallback = CPhysicsSystem::contactCallbackFunction;
    // entityx event we subscribe to
    event_manager->subscribe<ComponentAddedEvent<PhysicsGhostComponent>>(*this);
    event_manager->subscribe<ComponentAddedEvent<PhysicsComponent>>(*this);
}
void CPhysicsSystem::receive(const ComponentAddedEvent<PhysicsGhostComponent> &physicsghostcomponent)
{
    entityx::Entity ent = physicsghostcomponent.entity;
    entityx::ptr<PhysicsGhostComponent> gho = physicsghostcomponent.component;

    /** TODO (ersitzt#1#12.10.2013): Find a way to add userPointer to an Entity for CollisionCallback */
    entityx::ptr<PhysicsComponent> phys = ent.component<PhysicsComponent>();
    if(phys)
    {
        gho->ghost->setUserPointer(reinterpret_cast<void*>(new BulletCallbackHelper(ent.id(), emptr)));
    }

    dynamicsWorld->addCollisionObject(gho->ghost,btBroadphaseProxy::SensorTrigger,btBroadphaseProxy::AllFilter & ~btBroadphaseProxy::SensorTrigger);

}
void CPhysicsSystem::receive(const ComponentAddedEvent<PhysicsComponent> &physicscomponent)
{
    entityx::ptr<PhysicsComponent> phys = physicscomponent.component;
    entityx::Entity entity = physicscomponent.entity;
    // alec
    //phys->rigidBody->setUserPointer(reinterpret_cast<void*>(entity.id().id()));
    phys->rigidBody->setUserPointer(reinterpret_cast<void*>(new BulletCallbackHelper(entity.id(), emptr)));


    /** TODO (ersitzt#2#12.10.2013): Find a way to add userPointer to an Entity for CollisionCallback */

    dynamicsWorld->addRigidBody(phys->rigidBody);

}
void CPhysicsSystem::update(entityx::ptr<EntityManager> es, entityx::ptr<EventManager> events, double dt)
{

#ifdef DEBUG
    std::cout << "Physics Update" << std::endl;
#endif // DEBUG

    dynamicsWorld->stepSimulation(1/60.f,10);
    checkGhostCollision();
}

void CPhysicsSystem::checkGhostCollision()
{
    int i;

    for (i=0; i<dynamicsWorld->getCollisionObjectArray().size(); i++)
    {
        btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
        btRigidBody* body = btRigidBody::upcast(obj);

        btAlignedObjectArray < btCollisionObject* > objsInsidePairCachingGhostObject;
        btAlignedObjectArray < btCollisionObject* >* pObjsInsideGhostObject = NULL;
        btGhostObject* ghost = btGhostObject::upcast(obj);

        if(ghost)
        {
            objsInsidePairCachingGhostObject.resize(0);
            pObjsInsideGhostObject = &ghost->getOverlappingPairs();
#ifdef DEBUG
            std::cout << ghost->getNumOverlappingObjects() << std::endl;
#endif // DEBUG

            processGhostCollisions(*pObjsInsideGhostObject, ghost);
        }
    }
}

void CPhysicsSystem::processGhostCollisions(btAlignedObjectArray<btCollisionObject*>& obj, btGhostObject *ghost)
{
#ifdef DEBUG
    std::cout << "Ghost Loop" << std::endl;
#endif // DEBUG
    btTransform ghosttrans = ghost->getWorldTransform();
    btVector3 ghostpos = ghosttrans.getOrigin();
    for (int i=0; i<obj.size(); i++)
    {
        btCollisionObject* o = obj[i];
        btRigidBody *b = btRigidBody::upcast(o);
        btRigidBody *ghostbody = (btRigidBody*)ghost->getUserPointer();

        BulletCallbackHelper *helper = reinterpret_cast<BulletCallbackHelper*>(b->getUserPointer());
        entityx::EntityManager *mgr = (entityx::EntityManager*)(helper->entitymanager);
        entityx::Entity ghostent = mgr->get(helper->entityid);
        entityx::ptr<PhysicsGhostComponent> ghostcomp = ghostent.component<PhysicsGhostComponent>();

        if(NULL != b && !ghostcomp)
        {
            btTransform trans;
            b->getMotionState()->getWorldTransform(trans);

            btVector3 origin = trans.getOrigin();
            btScalar dist = origin.distance(ghostpos);
            btVector3 impulsedirection = ghostpos - origin;
            impulsedirection = impulsedirection.normalized();
            b->applyCentralImpulse(impulsedirection * (100 / dist) * 0.2);
        }

    }

}
