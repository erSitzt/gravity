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
        inputcomp->down = down;
        inputcomp->left = left;
        inputcomp->right = right;
    }
    up = false;
    down = false;
    left = false;
    right = false;



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
        std::cout << "Taste gedrückt!" << std::endl;
        up = true;
        break;
    case input::KEY_DOWN:
        std::cout << "Taste gedrückt!" << std::endl;
        down = true;
        break;
    case input::KEY_LEFT:
        std::cout << "Taste gedrückt!" << std::endl;
        left = true;
        break;
    case input::KEY_RIGHT:
        std::cout << "Taste gedrückt!" << std::endl;
        right = true;
        break;
    default:
        break;
    }
}
