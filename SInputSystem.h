#ifndef SINPUTSYSTEM_H
#define SINPUTSYSTEM_H

#include <lf/Lightfeather.h>
#include "entityx.h"
#include "events.h"
#include "components.h"

using namespace lf;
using namespace entityx;

struct SInputSystem : public System<SInputSystem>, Receiver<SInputSystem> ,input::IKeyListener, input::IMouseListener
{
    public:
        SInputSystem();
        virtual ~SInputSystem();
        void configure(entityx::ptr<EventManager> event_manager);
        void update(entityx::ptr<EntityManager> es, entityx::ptr<EventManager> events, double dt);
        void keyPressed(input::CKeyEvent& event);
        void keyReleased(input::CKeyEvent& event);

        bool left;
        bool right;
        bool up;
        bool down;


};

#endif // SINPUTSYSTEM_H
