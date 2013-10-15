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
    event_manager->subscribe<ListenerPositionChangedEvent>(*this);
    sf::Listener::setPosition(10.f, 0.f, 5.f);


}
void SSoundSystem::update(entityx::ptr<EntityManager> es, entityx::ptr<EventManager> events, double dt)
{
    for (auto entity : es->entities_with_components<SoundComponent>())
    {
        entityx::ptr<SoundComponent> soundcomp = entity.component<SoundComponent>();
        entityx::ptr<PositionComponent> pos = entity.component<PositionComponent>();
        if(pos)
        {
            soundcomp->sound.setPosition(pos->x, pos->y, pos->z);
        }
        if(soundcomp->sound.getStatus() != sf::Sound::Statusi::Playing && soundcomp->playme == true)
        {
            soundcomp->sound.play();
            soundcomp->playme = false;
        }
    }
}
void SSoundSystem::receive(const ListenerPositionChangedEvent &listenerposchange)
{
    sf::Listener::setPosition(listenerposchange.pos.X, listenerposchange.pos.Y, listenerposchange.pos.Z);
}
void SSoundSystem::setListenerPosition(core::vector3df pos)
{
    sf::Listener::setPosition(pos.X, pos.Y, pos.Z);
}
