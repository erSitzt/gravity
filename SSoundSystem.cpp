#include "SSoundSystem.h"

SSoundSystem::SSoundSystem()
{
    //ctor
}

SSoundSystem::~SSoundSystem()
{
    //dtor
}
void SSoundSystem::configure(entityx::ptr<EventManager> event_manager)
{
    std::cout << "SSoundSystem configure" << std::endl;


}
void SSoundSystem::update(entityx::ptr<EntityManager> es, entityx::ptr<EventManager> events, double dt)
{
    for (auto entity : es->entities_with_components<SoundComponent>())
    {
        entityx::ptr<SoundComponent> soundcomp = entity.component<SoundComponent>();
        //soundcomp->sound.play();
    }
}
