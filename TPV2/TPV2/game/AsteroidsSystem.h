#pragma once
#include "../ecs_4/ecs/System.h"
#include <vector>
#include "../ecs_4/ecs/Entity.h"
#include "../components/Generations.h"


class Entity;

class AsteroidsSystem : public System {
public:
	// - a�ade n asteroides al juego como en la pr�ctica 1.
	void addAsteroids(int n);
	// - desactivar el asteroide �a� y crear 2 asteroides como en la pr�ctica 1.
	// - pasamos una referencia a la bala aunque no se usa de momento (en el futuro
	// se puede usar para tener comportamientos distintos depende del tipo de
	// bala, etc.)
	// - si no hay m�s asteroides avisar al GameCtrlSystem
	void onCollisionWithBullet(Entity* a, Entity* b) ;
	// - si el juego est� parado no hacer nada.
	// - mover los asteroides como en la pr�ctica 1.
	void update() override;

	void getEntities(const std::vector<Entity*>* ent) { entidades = ent; }

	

private:
	int numOfAsteroids_;
	void addAsteroid();
	const std::vector<Entity*>* entidades;
	void divideAsteroide(Entity* a, Generations* gen);

};
