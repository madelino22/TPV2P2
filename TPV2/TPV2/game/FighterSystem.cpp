#include "FighterSystem.h"
#include "../ecs_4/ecs/Manager.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"


void FighterSystem::onCollisionWithAsteroid(Entity* a)
{
}

void FighterSystem::init()
{
	//esto iría en el fighterSystem
	Entity* fighter = manager_->addEntity();
	manager_->addComponent<Transform>(fighter, Vector2D(sdlutils().width() / 2, sdlutils().height() / 2), Vector2D(0, 0), 20, 20, 0);
	manager_->setHandler<JET>(fighter);

}

void FighterSystem::update()
{
}
