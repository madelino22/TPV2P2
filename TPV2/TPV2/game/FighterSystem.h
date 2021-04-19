#pragma once

#pragma once
#include "../ecs_4/ecs/System.h"
#include "../ecs_4/ecs/Entity.h"
#include <vector>


class FighterSystem :
    public System
{
public:
    void onCollisionWithAsteroid(Entity* a);
    void init() override;
    void update() override;
private:

};