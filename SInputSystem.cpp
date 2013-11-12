#include "SInputSystem.h"

using namespace lf;
using namespace entityx;

SInputSystem::SInputSystem()
{
    rwin = CLFRender::getInstance().getRenderWindow(0);

    rwin->addKeyListener(this);
    rwin->addMouseMovementListener(this);
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
    for (auto entity : es->entities_with_components<PlayerComponent>())
    {
        entityx::ptr<InputComponent> inputcomp = entity.component<InputComponent>();
        inputcomp->yaw = yaw;
        inputcomp->pitch = pitch;
    }

}
void SInputSystem::configure(entityx::ptr<EventManager> event_manager)
{
    std::cout << "SInputSystem configure" << std::endl;
    mouseControl = rwin->getCursorControl();

}

void SInputSystem::keyPressed(input::CKeyEvent& event)
{
    std::cout << "Taste gedrückt!" << std::endl;
    switch(event.getKey())
    {
    case input::KEY_UP:
        up = true;
        break;
    case input::KEY_DOWN:
        down = true;
        break;
    case input::KEY_LEFT:
        left = true;
        break;
    case input::KEY_RIGHT:
        right = true;
        break;
    default:
        break;
    }
}
void SInputSystem::keyReleased(input::CKeyEvent& event)
{
    switch(event.getKey())
    {
    case input::KEY_UP:
        std::cout << "Taste losgelassen!" << std::endl;
        up = false;
        break;
    case input::KEY_DOWN:
        std::cout << "Taste losgelassen!" << std::endl;
        down = false;
        break;
    case input::KEY_LEFT:
        std::cout << "Taste losgelassen!" << std::endl;
        left = false;
        break;
    case input::KEY_RIGHT:
        std::cout << "Taste losgelassen!" << std::endl;
        right = false;
        break;
    default:
        break;
    }
}
void SInputSystem::mouseMoved(input::CMouseEvent& event)
{
    core::vector2d<f32> cursorpos = mouseControl->getRelativePosition();

    if( fabs(cursorpos.X - 0.5f) >= 0.001 || fabs(cursorpos.Y - 0.5f) >= 0.001 )
    {

        yaw = event.getPosX() - event.getOldX();
        pitch = event.getPosY() - event.getOldY();
        mouseControl->setPosition( 0.5f, 0.5f );
    }


}
