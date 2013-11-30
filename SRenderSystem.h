#ifndef SRENDERSYSTEM_H
#define SRENDERSYSTEM_H

#include <lf/Lightfeather.h>
#include "entityx.h"
#include "events.h"
#include "components.h"
#include "SSoundSystem.h"

using namespace lf;
using namespace entityx;

struct SRenderSystem : public System<SRenderSystem>, Receiver<SRenderSystem> ,input::IKeyListener, input::IMouseListener
{
public:
    SRenderSystem();
    virtual ~SRenderSystem();
    void configure(entityx::ptr<EventManager> event_manager);
    void receive(const PositionChangedEvent &poschange);
    void receive(const ComponentAddedEvent<ModelComponent> &modelcomponent);
    void receive(const ComponentAddedEvent<CameraComponent> &cameracomponent);
    void receive(const ComponentAddedEvent<PlayerComponent> &playercomponent);
    void receive(const ComponentAddedEvent<LightComponent> &lightcomponent);
    void update(entityx::ptr<EntityManager> es, entityx::ptr<EventManager> events, double dt);
    void setup2D();
    void setupScene();
    void keyPressed(input::CKeyEvent& event);
    void mouseClicked(input::CMouseEvent& event);

    entityx::ptr<EventManager> events;
    render::IRenderWindow *rwin;
    scene::CScene *scn;
    scene::C3DCamera *cam;
    scene::CLight *light;
    u32 lastFPS;
    u32 lastPolyCount;

};

#endif // SRENDERSYSTEM_H
