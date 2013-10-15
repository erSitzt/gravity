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
CTutorial1::CTutorial1()
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

    while(!quitNow)
    {
        manager.run();
    }
}

