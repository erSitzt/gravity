#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <entityx.h>
#include "components.h"
#include "systems.h"
#include "EntityMotionState.h"

using namespace entityx;

class GameManager : public Manager
{
public:
    GameManager();
    virtual ~GameManager();
protected:
    void configure();
    void initialize();
    void update(double dt);
private:
};

#endif // GAMEMANAGER_H
