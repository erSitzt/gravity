#include "SWeaponSystem.h"

SWeaponSystem::SWeaponSystem()
{
    //ctor
}

SWeaponSystem::~SWeaponSystem()
{
    //dtor
}
void SWeaponSystem::configure(entityx::ptr<EventManager> event_manager)
{
    std::cout << "SWeaponSystem configure" << std::endl;
    event_manager->subscribe<WeaponEvent>(*this);

}
void SWeaponSystem::update(entityx::ptr<EntityManager> es, entityx::ptr<EventManager> events, double dt)
{

}
void SWeaponSystem::receive(const WeaponEvent &weapon)
{
    std::cout << "Player Weapon fired" << std::endl;
//    entityx::Entity entity = weapon.entity;
//    entityx::ptr<WeaponComponent> weaponcomp = entity.component<WeaponComponent>();
//    entityx::ptr<PositionComponent> pos = entity.component<PositionComponent>();

}
