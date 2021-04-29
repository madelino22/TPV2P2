#pragma once
#include "../ecs_4/ecs/System.h"
#include "../ecs_4/ecs/Entity.h"
#include <vector>
#include "../utils/Vector2D.h"
#include "../sdlutils/InputHandler.h"
#include "../components/Transform.h"
class BulletsSystem : public System
{
public:

	void shoot(Vector2D pos, Vector2D vel, double width, double height);
	void update() override;
	void getEntities(const std::vector<Entity*>* ent) { entidades = ent; }
	void init() override;
private:
	Transform* tr_; // Tranform de la nave
	const std::vector<Entity*>* entidades;
};

