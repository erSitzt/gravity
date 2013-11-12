#include "GameManager.h"

using namespace entityx;

GameManager::GameManager()
{
    //ctor
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
    system_manager->add<CPhysicsSystem>(entity_manager);
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

/** TODO (ersitzt#1#): Move resource loading somewhere else
create ModelComponent only by ResourceName ??? */

    core::stringc blenderDir = "/home/ersitzt/Blender";
    CLFPersistence::getInstance().getFileSystem()->addSearchPath(blenderDir.c_str());
    CLFPersistence::getInstance().load("asteroid3.lfm");
    res::CModel *model = CResourceManager::getInstance().getResource<res::CModel>("asteroid3");
    model->getMesh(0)->getVertexBuffer()->setColor(0, 0, core::CColorI(255, 0, 0, 255));
    scene::CModelSceneNode *modelNode = new scene::CModelSceneNode(model);
    model->getMaterial(0)->setRenderFeature(render::ERPF_DIFFUSEMAP);

    entityx::Entity playerentity = entity_manager->create();
    playerentity.assign<PositionComponent>();
    playerentity.assign<RotationComponent>();
    entityx::ptr<PositionComponent> playerpos = playerentity.component<PositionComponent>();
    entityx::ptr<RotationComponent> playerrot = playerentity.component<RotationComponent>();
    playerentity.assign<SoundComponent>("/home/ersitzt/impact.wav");
    playerentity.assign<ModelComponent>(model);
    playerentity.assign<InputComponent>();
    playerentity.assign<PlayerComponent>();
    playerentity.assign<PhysicsComponent>(new btSphereShape(btScalar(5)), new EntityMotionState(btTransform(playerrot->getRotationBT(), playerpos->getPositionBT()), playerentity, event_manager), 1000, btVector3(0,0,0));
    playerentity.assign<CameraComponent>(CLFRender::getInstance().getRenderWindow(0));


    for(int i = 0; i<=50; i++)
    {
        entityx::Entity tmpentity = entity_manager->create();
        tmpentity.assign<PositionComponent>(CLFOS::getInstance().getRandomizer()->randf() * i + 10,CLFOS::getInstance().getRandomizer()->randf() *i +10,CLFOS::getInstance().getRandomizer()->randf()*i +10);
        tmpentity.assign<RotationComponent>();
        entityx::ptr<PositionComponent> position = tmpentity.component<PositionComponent>();
        entityx::ptr<RotationComponent> rotation = tmpentity.component<RotationComponent>();
        tmpentity.assign<SoundComponent>("/home/ersitzt/impact.wav");
        tmpentity.assign<ModelComponent>(model);


        if(i == 0)
        {
            //tmpentity.assign<InputComponent>();
            tmpentity.assign<PhysicsComponent>(new btSphereShape(btScalar(5)), new EntityMotionState(btTransform(rotation->getRotationBT(), position->getPositionBT()), tmpentity, event_manager), 1000, btVector3(0,0,0));
            //tmpentity.assign<PhysicsGhostComponent>(new btSphereShape(btScalar(10000)), position->getPositionBT());
            tmpentity.assign<CameraComponent>(core::recti(210,10,410,200));
            tmpentity.assign<LightComponent>(core::CColorF(0.4f, 0.0f, 0.0f, 1.0f));

        }
        else if(i == 1)
        {
            //tmpentity.assign<InputComponent>();
            tmpentity.assign<PhysicsComponent>(new btSphereShape(btScalar(5)), new EntityMotionState(btTransform(rotation->getRotationBT(), position->getPositionBT()), tmpentity, event_manager), 10, btVector3(0,0,0));
            tmpentity.assign<CameraComponent>(core::recti(10,10,200,200));
            tmpentity.assign<LightComponent>(core::CColorF(0.4f, 111.0f, 111.0f, 1.0f));

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
