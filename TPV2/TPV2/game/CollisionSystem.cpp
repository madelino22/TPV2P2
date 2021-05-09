#include "CollisionSystem.h"
#include "../ecs_4/ecs/Manager.h"
#include "../utils/Collisions.h"
#include "AsteroidsSystem.h"

void CollisionSystem::update() {
	int n = (*entidades).size();
	//Se recorre la lista de entidades
	for (int i = 0; i < n; ++i)
		//para cada entidad del grupoi asteroides
		if (manager_->hasGroup<Asteroids>((*entidades)[i]))
		{
			auto aTR =  manager_->getComponent<Transform>( (*entidades)[i]);
			for (int j = 0; j < n; ++j)
				//se recorre otra vez la lista preguntando a las entidades del grupo balas o a la nave
				if (manager_->hasGroup<Bullets>((*entidades)[j])) // Choque con las balas
				{
					auto bTR = manager_->getComponent<Transform>((*entidades)[j]);
					//si han chocado
					if (Collisions::collidesWithRotation(aTR->getPos(), aTR->getW(), aTR->getH(), aTR->getRot(),
						bTR->getPos(), bTR->getW(), bTR->getH(), bTR->getRot()))
					{
						Message astBullColl;
						astBullColl.id_ = ASTEROID_COLLISION_WITH_BULLET;
						astBullColl.entitiesCol.asteroid = (*entidades)[i];
						astBullColl.entitiesCol.bullet = (*entidades)[j];
						manager_->send(astBullColl);
						
					}
				}
				else if ((*entidades)[j] == manager_->getHandler<JET>()) // Choque con la nave
				{
					auto jTR = manager_->getComponent<Transform>((*entidades)[j]);
					if (Collisions::collidesWithRotation(aTR->getPos(), aTR->getW(), aTR->getH(), aTR->getRot(),
						jTR->getPos(), jTR->getW(), jTR->getH(), jTR->getRot()))
					{
						Message collisionWithJet;
						collisionWithJet.id_ = JET_COLLISION_WITH_ASTEROID;
						collisionWithJet.jetCol.entity = (*entidades)[i];
						manager_->send(collisionWithJet);
							//getSystem<FighterSystem>()->onCollisionWithAsteroid((*entidades)[i]);
					}
				}

		}
}