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
						//manager_->getSystem<AsteroidsSystem>()->onCollisionWithBullet((*entidades)[i],(*entidades)[j]);
						//manager_->getSystem<BulletsSystem>()->onCollisionWithAsteroid((*entidades)[j],(*entidades)[i]);



						//todo esto lo hace el gamectrlsystem a través de la llamada a onCollisionWithBullet
						//if (entientidadesty_->getComponent<AsteroidsManager>()->getNumAsteroides() == 0)
						//{
						//	//si ya no quedan astaroides se gana la partida y se restablecen todas las variables
						//	entity_->getComponent<State>()->changeState(State::WON);
						//	auto tr_ = jet->getComponent<Transform>();
						//	tr_->setRot(0.0f);
						//	tr_->setVel(Vector2D(0, 0));
						//	tr_->setPos(Vector2D(sdlutils().width() / 2.0f, sdlutils().height() / 2.0f));

						//	//Además se quitan las componenten que hacen que se mueva en el menu para que no se mueva,
						//	//luego, al cargar otra vez partida, se le vuelven a añadir
						//	jet->removeComponent<FighterCtrl>();
						//	jet->removeComponent<Gun>();
						//}
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