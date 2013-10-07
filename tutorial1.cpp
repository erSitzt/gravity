// Copyright 2006-2008 by Lightfeather Team
// Written by Matthias Meyer
// This file is part of the Lightfeather 3D Engine.
// The license under which this code is distributed can be found in the file COPYING

/* Welcome to the first tutorial on how to use the Lightfeather engine (LF).
   First of all, you might be wondering why we do not use a simple/single
   source (*.cpp) file.
   The very first tutorial should be as simple as possible, right?
   The reason for this is that LF uses a listener based system for events,
   so in order to receive any event (like a key being pressed or mouse button
   clicked) you need to create a class that inherits from a
   listener interface class (more on this later).
   We could, of course, define a class within the main source file
   (the file you are looking at), but since we always define one class per
   .h/.cpp in LF, we won't deviate from that for the tutorials
   (so you get used to it).

   The only file you ever need to include in a program to use LF is
   lf/Lightfeather.h. For every directory in the LF directory hierarchy
   there is an include file at the same level as the directory itself
   which includes all header files for that directory.
   Take, for example, the main LF include directory (include/lf):
   d core
   d input
   d log
   d net
   d os
   d render
   d resources
   d scene
   d sound
   d threads
   d util
   - LfConfig.h
   - LfCore.h
   - LfInput.h
   - LfLog.h
   - LfMain.h
   - LfNet.h
   - LfOs.h
   - LfRender.h
   - LfResources.h
   - LfScene.h
   - LfSound.h
   - LfThread.h
   - LfUtil.h
   - Lightfeather.h
   For the core directory (d core) there is an LfCore.h, for the input
   directory there is an LfInput.h and so on.
   The only exception to this is the Lightfeather.h which is in that same
   directory and includes all of them. So no need to include anything besides
   lf/Lightfeather.h to use LF.
*/
#include <boost/asio.hpp>

#include <lf/Lightfeather.h>

#include "CTutorial1.h"

using namespace lf;
using boost::asio::ip::udp;
template <typename T>
using ptr = std::shared_ptr<T>;

int main(int argc, char *argv[])
{

boost::asio::io_service io_service;
udp::resolver resolver(io_service);
udp::resolver::query query(udp::v4(), "localhost", "daytime");
udp::endpoint receiver_endpoint = *resolver.resolve(query);


    lf::initLF();
    CTutorial1 *ex = new CTutorial1();

    ex->run();

    delete ex;
    lf::deinitLF();
    return 0;
}

// That's all for the initialization. Now go to CTutorial1.h/.cpp files.

