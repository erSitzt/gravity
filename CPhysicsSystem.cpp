#include "CPhysicsSystem.h"

CPhysicsSystem::CPhysicsSystem()
{
    //ctor
}

CPhysicsSystem::~CPhysicsSystem()
{
    //dtor
}
void CPhysicsSystem::configure(entityx::ptr<EventManager> event_manager)
{
    std::cout << "CPhysicsSystem configure" << std::endl;

    //Setup Bullet Physics

    // Build the broadphase
    btBroadphaseInterface* broadphase = new btDbvtBroadphase();

    // Set up the collision configuration and dispatcher
    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

    // The actual physics solver
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

    // The world.
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0,0,0));

    // Ghost-Objects
    btGhostPairCallback *ghostCall = new btGhostPairCallback();
    dynamicsWorld->getBroadphase()->getOverlappingPairCache()->setInternalGhostPairCallback(ghostCall);

    event_manager->subscribe<ComponentAddedEvent<PhysicsGhostComponent>>(*this);
    event_manager->subscribe<ComponentAddedEvent<PhysicsComponent>>(*this);
}
void CPhysicsSystem::receive(const ComponentAddedEvent<PhysicsGhostComponent> &physicsghostcomponent)
{
    entityx::Entity ent = physicsghostcomponent.entity;
    entityx::ptr<PhysicsGhostComponent> gho = physicsghostcomponent.component;
    // Check if this Entity also has PhysicsComponent
    entityx::ptr<PhysicsComponent> phys = ent.component<PhysicsComponent>();
    if(phys)
    {
        gho->ghost->setUserPointer(phys->rigidBody);
    }
    dynamicsWorld->addCollisionObject(gho->ghost,btBroadphaseProxy::SensorTrigger,btBroadphaseProxy::AllFilter & ~btBroadphaseProxy::SensorTrigger);

}
void CPhysicsSystem::receive(const ComponentAddedEvent<PhysicsComponent> &physicscomponent)
{
    entityx::ptr<PhysicsComponent> phys = physicscomponent.component;
    entityx::Entity ent = physicscomponent.entity;

    dynamicsWorld->addRigidBody(phys->rigidBody);

}
void CPhysicsSystem::update(entityx::ptr<EntityManager> es, entityx::ptr<EventManager> events, double dt)
{

#ifdef DEBUG
    std::cout << "Physics Update" << std::endl;
#endif // DEBUG
    for (auto entity : es->entities_with_components<InputComponent, PhysicsComponent>())
    {

        entityx::ptr<InputComponent> inp = entity.component<InputComponent>();
        if(inp->up == true)
        {
            entityx::ptr<PhysicsComponent> phys = entity.component<PhysicsComponent>();
            btVector3 vec = btVector3(0,1,0);
            vec = vec.normalized();
            phys->rigidBody->applyCentralImpulse(vec * 100);
            inp->up = false;
        }
    }
    for (auto entity : es->entities_with_components<InputComponent, PhysicsGhostComponent>())
    {

        entityx::ptr<InputComponent> inp = entity.component<InputComponent>();
        if(inp->up == true)
        {
            entityx::ptr<PhysicsGhostComponent> gho = entity.component<PhysicsGhostComponent>();
            btVector3 upDir = gho->ghost->getWorldTransform().getBasis()[1];
            upDir.normalize();
            btVector3 oldpos = gho->ghost->getWorldTransform().getOrigin();
            gho->ghost->getWorldTransform().setOrigin(oldpos + upDir);

            inp->up = false;
        }
    }
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
        if(NULL != b && b != ghostbody)
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
