#include "SInputSystem.h"

using namespace lf;
using namespace entityx;

SInputSystem::SInputSystem()
{
    rwin = CLFRender::getInstance().getRenderWindow(0);
    up = false;
    down = false;
    left = false;
    right = false;
    rwin->addKeyListener(this);
    rwin->addMouseListener(this);
    rotateXSpeed = 100.0f;
    rotateYSpeed = 100.0f;

    //ctor
}

SInputSystem::~SInputSystem()
{
    //dtor
}
void SInputSystem::update(entityx::ptr<EntityManager> es, entityx::ptr<EventManager> events, double dt)
{
    if( firstUpdate )
    {
        mouseControl->setPosition( 0.5f, 0.5f );

        core::vector2d<f32> cursorpos = mouseControl->getRelativePosition();
        rotX[0] = rotX[1] = (0.5f - cursorpos.X) * rotateXSpeed;
        rotY[0] = rotY[1] = (0.5f - cursorpos.Y) * rotateYSpeed;
        firstUpdate = false;
    }
    else
    {

        core::vector2d<f32> cursorpos = mouseControl->getRelativePosition();

        // warui smooth camera patch
        // puts values from this frame into table;
        rotX[2] = (0.5f - cursorpos.X) * rotateXSpeed;
        rotY[2] = (0.5f - cursorpos.Y) * rotateYSpeed;

        if( fabs(cursorpos.X - 0.5f) >= 0.0005 || fabs(cursorpos.Y - 0.5f) >= 0.0005 )
        {
            rotXAvg = ( rotX[0] + rotX[1] + rotX[2] ) / 3.0f;
            rotYAvg = ( rotY[0] + rotY[1] + rotY[2] ) / 3.0f;
            //std::cout << fabs(cursorpos.X - 0.5f) << " : " << fabs(cursorpos.Y - 0.5f) << std::endl;
            mouseControl->setPosition( 0.5f, 0.5f );
            yaw = -(rotXAvg);
            pitch = -(rotYAvg);
        }

        // finally we move values to make room for a new one
        rotX[0] = rotX[1];
        rotX[1] = rotX[2];

        rotY[0] = rotY[1];
        rotY[1] = rotY[2];

    }
    for (auto entity : es->entities_with_components<InputComponent>())
    {
        entityx::ptr<InputComponent> inputcomp = entity.component<InputComponent>();
        inputcomp->up = up;
        inputcomp->down = down;
        inputcomp->left = left;
        inputcomp->right = right;
        inputcomp->shift = shift;
        /** TODO (ersitzt#1#): test
         */

        inputcomp->yaw = yaw;
        inputcomp->pitch = pitch;
    }
    for (auto entity : es->entities_with_components<PlayerComponent>())
    {
        entityx::ptr<InputComponent> inputcomp = entity.component<InputComponent>();
        inputcomp->yaw = yaw;
        inputcomp->pitch = pitch;
    }
    yaw = 0;
    pitch = 0;

}
void SInputSystem::configure(entityx::ptr<EventManager> event_manager)
{
    std::cout << "SInputSystem configure" << std::endl;
    events = event_manager;
    mouseControl = rwin->getCursorControl();
    mouseControl->setPosition( 0.5f, 0.5f );
    mouseControl->setVisible( false );

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
    case input::KEY_LSHIFT:
        shift = true;
        std::cout << "Shift ON" << std::endl;
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
    case input::KEY_LSHIFT:
        shift = false;
        std::cout << "Shift OFF" << std::endl;
        break;
    default:
        break;
    }
}
void SInputSystem::mousePressed(input::CMouseEvent& event)
{
    std::cout << "Some Mouse Button pressed" << std::endl;
    if(event.getButton() == input::EMBM_BUTTON1)
    {
        this->events->emit<WeaponEvent>();
    }
}
