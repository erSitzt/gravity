#ifndef SINPUTSYSTEM_H
#define SINPUTSYSTEM_H

#include <lf/Lightfeather.h>
#include "entityx.h"
#include "events.h"
#include "components.h"

using namespace lf;
using namespace entityx;

struct SInputSystem : public System<SInputSystem>, Receiver<SInputSystem> ,input::IKeyListener, input::IMouseMovementListener
{
    public:
        SInputSystem();
        virtual ~SInputSystem();
        void configure(entityx::ptr<EventManager> event_manager);
        void update(entityx::ptr<EntityManager> es, entityx::ptr<EventManager> events, double dt);
        void keyPressed(input::CKeyEvent& event);
        void keyReleased(input::CKeyEvent& event);
        void mouseMoved(input::CMouseEvent& event);


        bool left;
        bool right;
        bool up;
        bool down;
            s16 yaw;
    s16 pitch;
    s16 roll;

    input::ICursorControl *mouseControl;
    render::IRenderWindow *rwin;


};

#endif // SINPUTSYSTEM_H
