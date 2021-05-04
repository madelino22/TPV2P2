
#pragma once
#include "../ecs_4/ecs/System.h"
#include "../ecs_4/ecs/Entity.h"
#include <vector>
#include "../utils/Vector2D.h"
#include "BulletsSystem.h"

class FighterSystem :
    public System
{
public:
    void onCollisionWithAsteroid(Entity* a);
    void init() override;
    void update() override;
    virtual void receive(const Message&);
private:
    Transform* tr;
    float thrust = 0.2;
    float speedLimit = 3;
    int lives = 3;
    BulletsSystem* bulletsSystem;
};