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
    virtual void keyPressed(input::CKeyEvent& event);
    virtual void keyReleased(input::CKeyEvent& event);
    virtual void mousePressed(input::CMouseEvent& event);

    bool firstUpdate;
    bool left;
    bool right;
    bool up;
    bool down;
    bool shift;
    f32 yaw;
    f32 pitch;
    f32 roll;
    f32 rotX[3];
    f32 rotY[3];
    f32 rotXAvg;
    f32 rotYAvg;
    f32 rotateXSpeed;
    f32 rotateYSpeed;
    f32 timeDiff;


    input::ICursorControl *mouseControl;
    render::IRenderWindow *rwin;
    entityx::ptr<EventManager> events;


};

#endif // SINPUTSYSTEM_H
