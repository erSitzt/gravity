#include "EntityMotionState.h"

EntityMotionState::EntityMotionState(const btTransform &initialpos, entityx::Entity entity, entityx::ptr<EventManager> events)
{
    //ctor
    this->events = events;
    this->entity = entity;
    mPos1 = initialpos;
}

EntityMotionState::~EntityMotionState()
{
    //dtor
}
void EntityMotionState::setEntity(entityx::Entity entity)
{
    entity = entity;
}
void EntityMotionState::getWorldTransform(btTransform &worldTrans) const
{
    worldTrans = mPos1;
}
void EntityMotionState::setWorldTransform(const btTransform &worldTrans)
{
    if(NULL == this->entity)
        return;
    entityx::ptr<PositionComponent> pos = entity.component<PositionComponent>();
    if(pos)
    {
        pos->setPosition(worldTrans.getOrigin());
#ifdef DEBUG
        std::cout << pos->x << " - " << pos->y << " - " << pos->z << std::endl;
#endif // DEBUG
    }
    entityx::ptr<RotationComponent> rot = entity.component<RotationComponent>();
    if(rot)
    {
        btQuaternion myquat = worldTrans.getRotation();
        rot->setRotation(myquat);
    }

    entityx::ptr<PhysicsGhostComponent> ghost = entity.component<PhysicsGhostComponent>();
    if(ghost)
    {
        btTransform ghotrans = ghost->ghost->getWorldTransform();
#ifdef DEBUG
        std::cout << "Origin   : " << ghotrans.getOrigin().x() << " - " << ghotrans.getOrigin().y() << " - " << ghotrans.getOrigin().z() << std::endl;
        std::cout << "Rotation : " << ghotrans.getRotation().x() << " - " << ghotrans.getRotation().y() << " - " << ghotrans.getRotation().z() << " - " <<  ghotrans.getRotation().w() <<std::endl;
        std::cout << "---------------" << std::endl;
        std::cout << "Origin   : " << worldTrans.getOrigin().x() << " - " << worldTrans.getOrigin().y() << " - " << worldTrans.getOrigin().z() << std::endl;
        std::cout << "Rotation : " << worldTrans.getRotation().x() << " - " << worldTrans.getRotation().y() << " - " << worldTrans.getRotation().z() << " - " <<  worldTrans.getRotation().w() <<std::endl;
#endif // DEBUG
        ghost->ghost->setWorldTransform(worldTrans);

    }

    this->events->emit<PositionChangedEvent>(this->entity);
    mPos1 = worldTrans;



}
