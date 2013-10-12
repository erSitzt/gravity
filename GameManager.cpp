#include "GameManager.h"


GameManager::GameManager()
{
    //ctor
    // EntityX
    events = entityx::EventManager::make();
    em = entityx::EntityManager::make(events);

}

GameManager::~GameManager()
{
    //dtor
}
void GameManager::configure()
{
#ifdef DEBUG
    std::cout << "GameManager configure" << std::endl;
#endif // DEBUG
    system_manager->add<CPhysicsSystem>(em);
    system_manager->add<SRenderSystem>();
    system_manager->add<SInputSystem>();
    system_manager->add<SMovementSystem>();
    system_manager->add<SSoundSystem>();
}
void GameManager::initialize()
{
#ifdef DEBUG
    std::cout << "GameManager initialize" << std::endl;
#endif // DEBUG

    core::stringc blenderDir = "/home/ersitzt/Blender";
    CLFPersistence::getInstance().getFileSystem()->addSearchPath(blenderDir.c_str());
    CLFPersistence::getInstance().load("asteroid6.lfm");
    res::CModel *model = CResourceManager::getInstance().getResource<res::CModel>("Mine.mesh");
    model->getMesh(0)->getVertexBuffer()->setColor(0, 0, core::CColorI(255, 0, 0, 255));
    scene::CModelSceneNode *modelNode = new scene::CModelSceneNode(model);

    for(int i = 0; i<=50; i++)
    {
        entityx::Entity tmpentity = entity_manager->create();
        tmpentity.assign<PositionComponent>(CLFOS::getInstance().getRandomizer()->randf() * i + 10,CLFOS::getInstance().getRandomizer()->randf() *i +10,CLFOS::getInstance().getRandomizer()->randf()*i +10);
        tmpentity.assign<RotationComponent>();
        entityx::ptr<PositionComponent> position = tmpentity.component<PositionComponent>();
        entityx::ptr<RotationComponent> rotation = tmpentity.component<RotationComponent>();
        tmpentity.assign<ModelComponent>(model);


        if(i == 0)
        {
            tmpentity.assign<InputComponent>();
            tmpentity.assign<SoundComponent>("/home/ersitzt/test.wav");
            tmpentity.assign<PhysicsComponent>(new btSphereShape(btScalar(5)), new EntityMotionState(btTransform(rotation->getRotationBT(), position->getPositionBT()), tmpentity, event_manager), 1000, btVector3(0,0,0));
            /** TODO (ersitzt#1#12.10.2013): GhostComponent not working until userPointer in Bullet is working */

            tmpentity.assign<PhysicsGhostComponent>(new btSphereShape(btScalar(10000)), position->getPositionBT());


        }
        else if(i == 1)
        {
            tmpentity.assign<InputComponent>();
            tmpentity.assign<PhysicsComponent>(new btSphereShape(btScalar(5)), new EntityMotionState(btTransform(rotation->getRotationBT(), position->getPositionBT()), tmpentity, event_manager), 10, btVector3(0,0,0));
        }
        else
        {
            tmpentity.assign<PhysicsComponent>(new btSphereShape(btScalar(5)), new EntityMotionState(btTransform(rotation->getRotationBT(), position->getPositionBT()), tmpentity, event_manager), 10, btVector3(0,0,0));
        }





    }
}

void GameManager::update(double dt)
{
#ifdef DEBUG
    std::cout << "GameManager update" << std::endl;
#endif // DEBUG
    system_manager->update<SInputSystem>(dt);
    system_manager->update<SMovementSystem>(dt);
    system_manager->update<CPhysicsSystem>(dt);
    system_manager->update<SSoundSystem>(dt);
    system_manager->update<SRenderSystem>(dt);
}
