
#pragma once
#include "../ecs_4/ecs/System.h"
#include "../ecs_4/ecs/Entity.h"
#include <vector>
#include "../utils/Vector2D.h"
#include "BulletsSystem.h"

class CollisionSystem :
    public System
{
public:
    void getEntities(const std::vector<Entity*>* ent) { entidades = ent; }
    void update() override;
private:
    const std::vector<Entity*>* entidades;

};