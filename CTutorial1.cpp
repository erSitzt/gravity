// Copyright 2006-2008 by Lightfeather Team
// Written by Matthias Meyer
// This file is part of the Lightfeather 3D Engine.
// The license under which this code is distributed can be found in the file COPYING

// Include the header for this class.
#include "CTutorial1.h"
#include "SPhysicsGhostComponent.h"

#include <iostream>


using namespace lf;
using namespace entityx;

// Set lastFPS and lastPolyCount to 0 so they will be updated
// in the first frame.
CTutorial1::CTutorial1() : lastFPS(0), lastPolyCount(0)
{

//    rwin = CLFRender::getInstance().createRenderWindow(
//               core::vector2di(300, 0), // Position of the upper left corner
//               core::vector2d<s32>(1280, 1024), // Size of the window.
//               32, // Number of color bits to use,
//               32, // Number of bits to use in the depth buffer.
//               render::EWCF_AUTOCLOSE, // This parameter is actually a list of
//               render::EAAF_16); // Anti-aliasing factor.
//
//    // Set default window caption.
//    rwin->setWindowCaption(L"Lightfeather Tutorial 1");
//    // Make the window visible. Since we didn't specify EWCF_VISIBLE,
//    // the window has been invisible until now.
//    rwin->setVisible(true);
//    // We register ourselves as a key listener with the render window
//    // (see CTutorial1.h for more details). CTutorial1 is the listener
//    // and the render window is the class that generates events.
//    rwin->addKeyListener(this);
//    rwin->addMouseListener(this);
//
//    // First find the application directory.
//    core::stringc mediaDir =
//        CLFOS::getInstance().getFileSystem()->getApplicationDirectory();
//    // Then add the relative path to the media directory.
//    mediaDir += "/../../examples/media";
//    // Finally add that directory to the search path of the
//    // persistence framework's filesystem.
//    CLFPersistence::getInstance().getFileSystem()->addSearchPath(mediaDir.c_str());
//
//    scn = rwin->getRenderLayer3D()->getScene();
//
//    CLFRender::getInstance().setAutoSleep(0);
    // Set up our 3D scene.
    //setupScene();
    // Set up our 2D render pane to display LF logo.
    //setup2D();

    manager.start();

}

// Destructor
CTutorial1::~CTutorial1()
{

}

// This method contains the main loop of the tutorial.
void CTutorial1::run()
{
    // Initialize the quit variable to false (we want to continue).
    bool quitNow = false;
    // If quitNow is set to false, because the CLFRender::update() method
    // returned false, we exit the loop and return the control
    // to the main() function in tutorial1.cpp.
    while(!quitNow)
    {
        /* Get the number of polygons rendered and the number of FPS.
           You can get polygon counts off each camera you are using
           or the total of polygons rendered in one render window which,
           of course, is the same if you only have one camera as we do in
           this tutorial.
           There are four different FPS values:
               rwin->getCurrentFPS()
                   current one;
               rwin->getOneSecondFPS()
                   over the last second;
               rwin->getFiveSecondFPS()
                   over the last 5 seconds;
               rwin->getThirtySecondFPS()
                   over the last 30 seconds.
        */
//        u32 polycount = rwin->getTotalPolygonCount();
//        u32 oneSecFPS = rwin->getOneSecondFPS();
//        // Only update the window caption if either the FPS,
//        // or the number of polygons has changed.
//        if(lastFPS != oneSecFPS || lastPolyCount != polycount)
//        {
//            wchar_t tmp[256];
//            snwprintf(tmp,
//                      256,
//                      L"Lightfeather Tutorial 1 - Polys: %u FPS(1sec): %d",
//                      polycount,
//                      oneSecFPS);
//            rwin->setWindowCaption(tmp);
//            lastFPS = oneSecFPS;
//            lastPolyCount = polycount;
//        }

        //btTransform trans;
        //fallRigidBody->getMotionState()->getWorldTransform(trans);

        //moved to PhysicsSystem
        //checkGhostCollision();
//
//        std::cout << "position : " << cam->getPosition().X << " - " << cam->getPosition().Y << " - " << cam->getPosition().Z << std::endl;
//        std::cout << "lightpos : " << light->getPosition().X << " - " << light->getPosition().Y << " - " << light->getPosition().Z << std::endl;
//        std::cout << "target   : " << cam->getTarget().X << " - " << cam->getTarget().Y << " - " << cam->getTarget().Z << std::endl;
//        // The update method handles all updates and rendering inside LF.
        // It returns false if there's nothing left to render (all render
        // windows have been closed). Otherwise it returns true.

        manager.run();
        //quitNow = !CLFRender::getInstance().update();

    }
}

void CTutorial1::setup2D()
{
    // CGUIManager is like a pane of glass that you put on top of the
    // 3D view and then paint on that so everything in the 3D view remains
    // visible besides the parts you overdraw in the GUI manager (in our case
    // that's just the region where the LF logo is being displayed).
    CLFPersistence::getInstance().load("gui/plastique.lfgt"); // Load GUI theme.
    gui::CGUIManager *pane = new gui::CGUIManager(
        core::CColorI(0, 0, 0, 255), // Color of the background, only used
        // when clearBuffers param is set.
        false); // clearBuffers: clear the background each frame. If you do
    // this while having a 3D view, the 3D view will be painted
    // over. So it's only useful to set this to true if you only
    // use 2D.
    // Add the GUI manager to the render window.
    rwin->addGUIManager(pane);
    // We can drop() the pane here since the render window has grabbed it
    // and will release it when it is closed.
    pane->drop();
    /* We load the LF logo as a texture, using defaults for texture parameters
       (which will be explained in a later tutorial). We name it lflogo
       so we can always access it by
           resourceManager->getTexture("lflogo")

       The file actually resides in the examples/media directory, but since
       we have added it as a search path we don't need to specify
       the full path here.
    */
    res::CTexture *ltexture = CLFPersistence::getInstance().loadTexture("lightfeather.png", "lflogo");
    // Now we draw the logo. Since we don't want to do anything else with it
    // (like moving it), we ignore the CSprite pointer that is returned.
    pane->drawImage(
        ltexture, // Texture to draw.
        core::vector2d<s32>(
            rwin->getInnerSize().X - 210,
            rwin->getInnerSize().Y - 128), // Position and...
        core::vector2d<s32>(256, 128), // size of the image on the screen.
        // Doesn't have to be the image size
        // as in our case.
        gui::ETT_TEST); // The render pass used to render the image
    // (see setupScene below for more details).
}

void CTutorial1::setupScene()
{
    // EntityX
    entityx::ptr<entityx::EventManager> events = entityx::EventManager::make();
    entityx::ptr<entityx::EntityManager> entities = entityx::EntityManager::make(events);

    // We create a 3D camera which is the camera with a perspective
    // projection (the default for any 3D application).
    cam = new scene::C3DCamera(rwin, core::PI / 3.0f, 1.0f, 1000.0f, true);
    cam->setBackgroundColor(core::CColorI(0, 0, 0, 0));
    cam->setPosition(core::vector3df(0.0f, 10.0f, -80.0f));
    scene::CFPSController *ctrl = new scene::CFPSController(rwin, cam, true);
    scn->addSceneNodeController(ctrl);
    ctrl->drop();
    rwin->getRenderLayer3D()->addCamera(cam);

    render::CRenderStateLighting *rstLgt = new render::CRenderStateLighting(true);
    cam->replaceRenderState(rstLgt);
    rstLgt->drop();


    light = new scene::CLight(
        core::CColorF(0.4f, 0.0f, 0.0f, 1.0f), // Diffuse color.
        core::CColorF(1.0f, 1.0f, 1.0f, 1.0f), // Specular highlights color.
        core::CColorF(0.0f, 0.0f, 0.0f, 1.0f), // Ambient color.
        200.0f, // Range (unused).
        0.0f,  // Constant attenuation.
        0.0f,  // Linear attenuation.
        1.0f / 500.0f, // Quadratic attenuation factor.
        0.0f); // Exponential attenuation factor.
    // Set the initial position of the light.
    light->setPosition(cam->getPosition());

    scn->addLight(light);
    // Since we want to add a child to the light (to see its position)
    // we also add it to the scene as a scene node.
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
    model->getMesh(0)->getVertexBuffer()->setColor(
        0, 0, core::CColorI(255, 0, 0, 255));
    scene::CModelSceneNode *modelNode = new scene::CModelSceneNode(model);


}


