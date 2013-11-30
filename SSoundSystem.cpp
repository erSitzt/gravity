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
    event_manager->subscribe<SoundEvent>(*this);

}
void SSoundSystem::update(entityx::ptr<EntityManager> es, entityx::ptr<EventManager> events, double dt)
{

}
void SSoundSystem::receive(const SoundEvent &sound)
{
    entityx::Entity entity = sound.entity;
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
void SSoundSystem::receive(const ListenerPositionChangedEvent &listenerposchange)
{
    sf::Listener::setPosition(listenerposchange.pos.X, listenerposchange.pos.Y, listenerposchange.pos.Z);
}
void SSoundSystem::setListenerPosition(core::vector3df pos)
{
    sf::Listener::setPosition(pos.X, pos.Y, pos.Z);
}
void SSoundSystem::receive(const ComponentAddedEvent<SoundComponent> &soundcomponent)
{
    entityx::ptr<SoundComponent> snd = soundcomponent.component;
    entityx::Entity entity = soundcomponent.entity;
}
void SSoundSystem::receive(const ComponentAddedEvent<ListenerComponent> &listenercomponent)
{
    entityx::ptr<ListenerComponent> listener = listenercomponent.component;
    entityx::Entity entity = listenercomponent.entity;
    entityx::ptr<PositionComponent> pos = entity.component<PositionComponent>();
    if(pos)
    {
        sf::Listener::setPosition(pos->x, pos->y, pos->z);

    }

}
