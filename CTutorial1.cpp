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


