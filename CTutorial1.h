// Copyright 2006-2008 by Lightfeather Team
// Written by Matthias Meyer
// This file is part of the Lightfeather 3D Engine.
// The license under which this code is distributed can be found in the file COPYING

// As usual, we include lf/Lightfeather.h and add the lf namespace.
#include <lf/Lightfeather.h>
#include <btBulletDynamicsCommon.h>
#include "entityx/entityx.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"
#include "GameManager.h"

using namespace lf;

// As explained above, we inherit from the key listener interface
// to be notified on events.
class CTutorial1
{
public:
    // Constructor.
    CTutorial1();
    // Destructor.
    ~CTutorial1();
    // This is the main method of the class which gets called after
    // instantiation from the example1.cpp's main() function.
    void run();
    // In this method we initialize the 2D display (used in this example
    // to display an LF logo).
    void setup2D();
    // This is the method used to setup our 3D view.
    void setupScene();


private:
    // Variables to hold our render window and scene
    // so we can access them from all methods of the class.
    render::IRenderWindow *rwin;
    scene::CScene *scn;
    // The camera we use to display the 3D view.
    scene::C3DCamera *cam;
    scene::CLight *light;
    // Variables to hold the number of FPS and number of polygons
    // of the last frame so we don't need to update the display of those
    // too often since changing the caption of a window is pretty slow.
    u32 lastFPS;
    u32 lastPolyCount;

    btRigidBody* fallRigidBody;
    GameManager manager;
};

