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


private:

    GameManager manager;
};

