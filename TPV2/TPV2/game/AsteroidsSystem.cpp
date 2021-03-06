#include "AsteroidsSystem.h"
#include "../ecs_4/ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "GameCtrlSystem.h"

using Point2D = Vector2D;

void AsteroidsSystem::addAsteroids(int n) {
	for (int x = 0; x < n; x++) {
		addAsteroid();
	}

}

void AsteroidsSystem::addAsteroid()
{
 	Entity* asteroide = manager_->addEntity();
	Generations* gen = manager_->addComponent<Generations>(asteroide);
	//se guarda gen para ponerle el tama?o inicial al asteroide
	int genNum = gen->getGenerations();

	//con este random se elige el margen en el que aparecer? el asateoride
	int posIniR = sdlutils().rand().nextInt(0, 4);

	Vector2D posIni;
	if (posIniR == 0) {
		posIni = Vector2D(0, sdlutils().rand().nextInt(0, sdlutils().height()));
	}
	else if (posIniR == 1) {
		posIni = Vector2D(sdlutils().width() - (10.0f + 5.0f * genNum), sdlutils().rand().nextInt(0, sdlutils().height()));
	}
	else if (posIniR == 2) {
		posIni = Vector2D(sdlutils().rand().nextInt(0, sdlutils().width()), 0);
	}
	else {
		posIni = Vector2D(sdlutils().rand().nextInt(0, sdlutils().width()), sdlutils().height()- (10.0f + 5.0f * genNum));

	}


	//c?lculo de velIni
	//point2d es un vector2d pero con el nombrecambiado para que sea m?s claro
	Point2D r = Point2D(sdlutils().rand().nextInt(0, 100), sdlutils().rand().nextInt(0, 100));
	//-50 para que quede centrado
	Point2D c = Point2D(sdlutils().width() / 2 - 50, sdlutils().height() / 2 - 50);

	c = c + r;

	//velocidad inicial con factor aleatorio
	Vector2D velIni = Vector2D((c - posIni).normalize() * (sdlutils().rand().nextInt(1, 10) / 10.0)
	);

	
	manager_->addComponent<Transform>(asteroide,
		posIni,
		velIni, 10.0f + 5.0f * genNum, 10.0f + 5.0f * genNum, 0.0f);

	//nuemro al azar que determina si es un asteroide de oro o no
	int gold = sdlutils().rand().nextInt(1, 10);
	if (gold >= 7) {
		gen->setGold();
		//asteroide->addComponent<Follow>(); el follow va en el UPDATE
	}
	
	//asteroide->addComponent<ShowAtOppositeSide>(); AL UPDATE
	manager_->setGroup<Asteroids>(asteroide, true);



	//se actualiza el contador de asteroides
	numOfAsteroids_++;
	std::cout << "Added: " << numOfAsteroids_ << "\n";

}


void AsteroidsSystem::divideAsteroide(Entity* as, Generations* genPadre)
{
	Entity* asteroide = manager_->addEntity();
	// Se coge el transform del asteroide del que proviene el nuevo
	auto as_tr = manager_->getComponent<Transform>(as);
	// La posici?n y velocidad del nuevo asteroide seran iguales a las del que proviene
	Vector2D p = as_tr->getPos();
	Vector2D v = as_tr->getVel();
	int w = as_tr->getW();
	// Se calcula su tama?o en base a las divisiones restantes
	auto size = 10.0f + 5.0f * genPadre->getGenerations();
	// Se calcula la rotaci?n de forma aleatoria
	int r = sdlutils().rand().nextInt(0, 360);
	manager_->addComponent<Transform>(asteroide, p + v.rotate(r) * 2 * w, v.rotate(r) * 1.1f, size, size, 0.0f);
	// Se podr? dividir una vez menos que su predecesor
	manager_->addComponent<Generations>(asteroide, genPadre->getGenerations() - 1);
	// Si el antiguo asteroide tenia el componente follow el nuevo tambien lo tendra, y ademas habra que usar el sprite dorado
	if (genPadre->isGold())manager_->getComponent<Generations>(asteroide)->setGold();
	// Si no lo ten?a, al nuevo no se le a?ade y se usa el sprite de asteroide normal

	manager_->setGroup<Asteroids>(asteroide, true);

	// Se actualiza el numero de asteroides
	numOfAsteroids_++;

	std::cout << "Added div" << numOfAsteroids_ << "\n";
}

void AsteroidsSystem::onCollisionWithBullet(Entity* a, Entity* b)
{
	// Se produce un sonido
	sdlutils().soundEffects().at("bangSmall").play();
	Generations* gen = manager_->getComponent<Generations>(a); 
	// Si al asteroide todav?a le quedaban divisiones, se divide en dos asteroides con una generaci?n menos
	if (gen->getGenerations() > 0)
	{
		divideAsteroide(a, gen);
		divideAsteroide(a, gen);
	}
	// Se desactiva el asteroide y se actualiza el numero total de los mismos
	manager_->setGroup<Asteroids>(a, false);
	//Desactiva el asteroide
	manager_->setActive(a, false);

	numOfAsteroids_--;

	if (numOfAsteroids_ <= 0) {
		Message noAsteroidsLeft;
		noAsteroidsLeft.id_ = ASTEROIDS_DESTROYED;
		manager_->send(noAsteroidsLeft);
	}
	std::cout << "Destroyed" <<numOfAsteroids_ << "\n";
}


void AsteroidsSystem::update() {
	
	if (manager_->getSystem<GameCtrlSystem>()->getGameState() == RUNNING)
	{
		//a?ade un asteroide periodicamente 
		if (sdlutils().currRealTime() >= timer + 10000) {
			timer = sdlutils().currRealTime();
			addAsteroid();
		}

	}


	//actualiza el movimiento del asteroide
	for (Entity* e : *entidades)
	{
		if (manager_->hasGroup<Asteroids>(e))
		{
			Transform* tr_asteroide = manager_->getComponent<Transform>(e);
			auto& pos = tr_asteroide->getPos();

			auto w = tr_asteroide->getW();
			auto h = tr_asteroide->getH();

			//si es de oro sigue al caza
			if (manager_->getComponent<Generations>(e)->isGold())
			{
				auto& q = manager_->getComponent<Transform>(manager_->getHandler<JET>())->getPos();
				auto& v = tr_asteroide->getVel();
				tr_asteroide->setVel(v.rotate(v.angle(q - pos) > 0 ? 1.0f : -1.0f));
			}

			tr_asteroide->setPos(pos + tr_asteroide->getVel());
			
			//salir por el otro lado de la pantalla
			if (pos.getX() + w / 2 < 0) {
				pos.setX(sdlutils().width() - w / 2);
			}
			else if (pos.getX() + w / 2 > sdlutils().width()) {
				pos.setX(-w / 2);
			}

			if (pos.getY() + h / 2 < 0) {
				pos.setY(sdlutils().height() - h / 2);
			}
			else if (pos.getY() + h / 2 > sdlutils().height()) {
				pos.setY(-h / 2);
			}
			
			
		}
	}

}

void AsteroidsSystem::receive(const Message& m)
{
	if (m.id_ == ASTEROID_COLLISION_WITH_BULLET)
		onCollisionWithBullet(m.entitiesCol.asteroid, m.entitiesCol.bullet);
	else if (m.id_ == JET_DESTROYED) {
		//cada vez que se destruye el caza se destruyen los asteroides asi que hay que actualizar el contador
		resetAsteroids();
	}
	
}


