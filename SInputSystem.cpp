#include "SInputSystem.h"

using namespace lf;
using namespace entityx;

SInputSystem::SInputSystem()
{
    render::IRenderWindow *rwin = CLFRender::getInstance().getRenderWindow(0);

    rwin->addKeyListener(this);
    rwin->addMouseListener(this);
    //ctor
}

SInputSystem::~SInputSystem()
{
    //dtor
}
void SInputSystem::update(entityx::ptr<EntityManager> es, entityx::ptr<EventManager> events, double dt)
{
    for (auto entity : es->entities_with_components<InputComponent>())
    {
        entityx::ptr<InputComponent> inputcomp = entity.component<InputComponent>();

        inputcomp->up = up;
    }
    up = false;


}
void SInputSystem::configure(entityx::ptr<EventManager> event_manager)
{
    std::cout << "SInputSystem configure" << std::endl;


}

void SInputSystem::keyPressed(input::CKeyEvent& event)
{
    // Just so you see that it gets triggered with every key press.
    // std::cout << "Key pressed" << std::endl;
    switch(event.getKey())
    {
    case input::KEY_UP:
        // We close the window, so on the next call to
        // CLFRender::update() it will return false and
        // the application will be terminated.
        std::cout << "Taste gedrückt!" << std::endl;
        up = true;
        break;
    default:
        break;
    }
}
