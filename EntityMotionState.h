#ifndef ENTITYMOTIONSTATE_H
#define ENTITYMOTIONSTATE_H

#include "entityx.h"
#include <btBulletDynamicsCommon.h>
#include "components.h"
#include "events.h"


using namespace entityx;

class EntityMotionState : public btMotionState
{
public:
    EntityMotionState(const btTransform &initialpos, entityx::Entity entity, entityx::ptr<EventManager> events);
    virtual ~EntityMotionState();
    void setEntity(entityx::Entity entity);
    virtual void getWorldTransform(btTransform &worldTrans) const;
    virtual void setWorldTransform(const btTransform &worldTrans);

protected:
    entityx::Entity entity;
    entityx::ptr<EventManager> events;
    btTransform mPos1;
private:
};


#endif // ENTITYMOTIONSTATE_H
