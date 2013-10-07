#include "SRenderSystem.h"

using namespace lf;

SRenderSystem::SRenderSystem()
{
    rwin = CLFRender::getInstance().createRenderWindow(
               core::vector2di(300, 0), // Position of the upper left corner
               core::vector2d<s32>(1280, 1024), // Size of the window.
               32, // Number of color bits to use,
               32, // Number of bits to use in the depth buffer.
               render::EWCF_AUTOCLOSE, // This parameter is actually a list of
               render::EAAF_NONE); // Anti-aliasing factor.

    // Set default window caption.
    rwin->setWindowCaption(L"Lightfeather Tutorial 1");
    // Make the window visible. Since we didn't specify EWCF_VISIBLE,
    // the window has been invisible until now.
    rwin->setVisible(true);
    // We register ourselves as a key listener with the render window
    // (see CTutorial1.h for more details). CTutorial1 is the listener
    // and the render window is the class that generates events.
    rwin->addKeyListener(this);
    rwin->addMouseListener(this);

    // First find the application directory.
    core::stringc mediaDir =
        CLFOS::getInstance().getFileSystem()->getApplicationDirectory();
    // Then add the relative path to the media directory.
    mediaDir += "/../../examples/media";
    // Finally add that directory to the search path of the
    // persistence framework's filesystem.
    CLFPersistence::getInstance().getFileSystem()->addSearchPath(mediaDir.c_str());

    scn = rwin->getRenderLayer3D()->getScene();

    CLFRender::getInstance().setAutoSleep(0);
}

SRenderSystem::~SRenderSystem()
{
    //dtor
}
void SRenderSystem::configure(entityx::ptr<EventManager> event_manager)
{
    std::cout << "SRenderSystem configure" << std::endl;
    event_manager->subscribe<ComponentAddedEvent<ModelComponent>>(*this);
    event_manager->subscribe<PositionChangedEvent>(*this);

    setup2D();
    setupScene();

}

void SRenderSystem::receive(const PositionChangedEvent &poschange)
{

    entityx::Entity ent = poschange.entity;
    entityx::ptr<ModelComponent> model = ent.component<ModelComponent>();
    entityx::ptr<PositionComponent> pos = ent.component<PositionComponent>();
    entityx::ptr<RotationComponent> rot = ent.component<RotationComponent>();
    if(model)
    {
        model->componentnode->setPosition(pos->getPositionLF());
        model->componentnode->setRotation(rot->getRotationLF());
        core::quaternion qt = rot->getRotationLF();
        //std::cout << "node : " << ent.id() << " pos : " << model->componentnode->getRotationQuaternion().X << " - " << model->componentnode->getRotationQuaternion().Y  << " - " << model->componentnode->getRotationQuaternion().Z  << std::endl;
    }
    //std::cout << "entity : " << ent.id() << " pos : " << pos->x << " - " << pos->y << " - " << pos->z << std::endl;


}
void SRenderSystem::receive(const ComponentAddedEvent<ModelComponent> &modelcomponent)
{
    entityx::ptr<ModelComponent> node = modelcomponent.component;
    entityx::Entity ent = modelcomponent.entity;
    entityx::ptr<PositionComponent> pos = ent.component<PositionComponent>();
    entityx::ptr<RotationComponent> rot = ent.component<RotationComponent>();
    scn->addSceneNode(node->componentnode);
    node->componentnode->setPosition(pos->getPositionLF());
    node->componentnode->setRotation(rot->getRotationLF());

}
void SRenderSystem::update(entityx::ptr<EntityManager> es, entityx::ptr<EventManager> events, double dt)
{
    u32 polycount = rwin->getTotalPolygonCount();
    u32 oneSecFPS = rwin->getOneSecondFPS();
    // Only update the window caption if either the FPS,
    // or the number of polygons has changed.
    if(lastFPS != oneSecFPS || lastPolyCount != polycount)
    {
        wchar_t tmp[256];
        snwprintf(tmp,
                  256,
                  L"Lightfeather Tutorial 1 - Polys: %u FPS(1sec): %d",
                  polycount,
                  oneSecFPS);
        rwin->setWindowCaption(tmp);
        lastFPS = oneSecFPS;
        lastPolyCount = polycount;
    }
    //std::cout << "cam : " << cam->getPosition().X << " - " << cam->getPosition().Y << " - " << cam->getPosition().Z <<std::endl;
    CLFRender::getInstance().update();
}

void SRenderSystem::setup2D()
{
    CLFPersistence::getInstance().load("gui/plastique.lfgt"); // Load GUI theme.
    gui::CGUIManager *pane = new gui::CGUIManager(core::CColorI(0, 0, 0, 255),false);
    rwin->addGUIManager(pane);
    pane->drop();
    res::CTexture *ltexture = CLFPersistence::getInstance().loadTexture("lightfeather.png", "lflogo");
    pane->drawImage(ltexture,core::vector2d<s32>(rwin->getInnerSize().X - 210,rwin->getInnerSize().Y - 128), core::vector2d<s32>(256, 128), gui::ETT_TEST);
}
void SRenderSystem::setupScene()
{

    btCollisionShape* fallShape = new btSphereShape(4);
    cam = new scene::C3DCamera(rwin, core::PI / 3.0f, 1.0f, 1000.0f, true);
    cam->setBackgroundColor(core::CColorI(0, 0, 0, 0));
    cam->setPosition(core::vector3df(0.0f, 0.0f, 0.0f));
    scene::CFPSController *ctrl = new scene::CFPSController(rwin, cam, true);
    scn->addSceneNodeController(ctrl);
    ctrl->drop();
    rwin->getRenderLayer3D()->addCamera(cam);
    render::CRenderStateLighting *rstLgt = new render::CRenderStateLighting(true);
    cam->replaceRenderState(rstLgt);
    rstLgt->drop();


    light = new scene::CLight(
        core::CColorF(0.4f, 0.0f, 0.0f, 1.0f), core::CColorF(1.0f, 1.0f, 1.0f, 1.0f), core::CColorF(0.0f, 0.0f, 0.0f, 1.0f), 200.0f, 0.0f, 0.0f, 1.0f / 500.0f, 0.0f);
    light->setPosition(cam->getPosition());
    scn->addLight(light);
    scn->addSceneNode(light);

    cam->drop();
    light->drop();

    cam->addChild(light);
    scene::CSceneStateLight *cstLgt = new scene::CSceneStateLight(light, true);
    scn->getRootSceneNode()->addSceneState(cstLgt);
    cstLgt->drop();

    core::stringc blenderDir = "/home/ersitzt/Blender";
    CLFPersistence::getInstance().getFileSystem()->addSearchPath(blenderDir.c_str());

    CLFPersistence::getInstance().load("asteroid7.lfm");

    res::CModel *model = CResourceManager::getInstance().getResource<res::CModel>("Asteroid.mesh");
    model->getMesh(0)->getVertexBuffer()->setColor(0, 0, core::CColorI(255, 0, 0, 255));
    scene::CModelSceneNode *modelNode = new scene::CModelSceneNode(model);

}

void SRenderSystem::keyPressed(input::CKeyEvent& event)
{
    // Just so you see that it gets triggered with every key press.
    // std::cout << "Key pressed" << std::endl;
    switch(event.getKey())
    {
    case input::KEY_ESCAPE:
        // We close the window, so on the next call to
        // CLFRender::update() it will return false and
        // the application will be terminated.
        rwin->closeWindow();
        break;
    default:
        break;
    }
}

void SRenderSystem::mouseClicked(input::CMouseEvent& event)
{
//    res::CModel *bulletmodel = CResourceManager::getInstance().getResource<res::CModel>("Asteroid.mesh");
//    bulletmodel->getMesh(0)->getVertexBuffer()->setColor(0, 0, core::CColorI(255, 255, 255, 255));
//    scene::CModelSceneNode *bulletNode = new scene::CModelSceneNode(bulletmodel);
//
//        btVector3 camtarget = btVector3(cam->getTarget().X ,cam->getTarget().Y,cam->getTarget().Z);
//        btVector3 camposition = btVector3(cam->getPosition().X ,cam->getPosition().Y,cam->getPosition().Z);
//        //btDefaultMotionState *motionstate = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), camposition));
//        GravityMotionState *motionstate = new GravityMotionState(btTransform(btQuaternion(0,0,0,1), camposition), bulletNode);
//        btScalar mass = 5;
//        btVector3 fallInertia(0,0,0);
//        btCollisionShape* fallShape = new btSphereShape(4);
//        fallShape->calculateLocalInertia(mass,fallInertia);
//        btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass,motionstate,fallShape,fallInertia);
//        fallRigidBody = new btRigidBody(fallRigidBodyCI);
//        dynamicsWorld->addRigidBody(fallRigidBody);
//        fallRigidBody->applyCentralImpulse((camtarget - camposition).normalized() * 5000);
//        scn->addSceneNode(bulletNode);
//        bulletNode->drop();

}

