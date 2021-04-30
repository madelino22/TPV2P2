#include "AsteroidsSystem.h"
#include "../ecs_4/ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Generations.h"

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
	//se guarda gen para ponerle el tamaño inicial al asteroide
	int genNum = gen->getGenerations();

	//con este random se elige el margen en el que aparecerá el asateoride
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


	//cálculo de velIni
	//point2d es un vector2d pero con el nombrecambiado para que sea más claro
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
	
}

void AsteroidsSystem::update() {
	
	for (Entity* e : *entidades)
	{
		if (manager_->hasGroup<Asteroids>(e))
		{
			Transform* tr_asteroide = manager_->getComponent<Transform>(e);
			auto& pos = tr_asteroide->getPos();

			auto w = tr_asteroide->getW();
			auto h = tr_asteroide->getH();

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

//
//void divideAsteroide(Entity* as, int gen)
//{
//	Entity* asteroide = entity_->getMngr()->addEntity();
//	// Se coge el transform del asteroide del que proviene el nuevo
//	auto as_tr = as->getComponent<Transform>();
//	// La posición y velocidad del nuevo asteroide seran iguales a las del que proviene
//	Vector2D p = as_tr->getPos();
//	Vector2D v = as_tr->getVel();
//	int w = as_tr->getW();
//	// Se calcula su tamaño en base a las divisiones restantes
//	auto size = 10.0f + 5.0f * gen;
//	// Se calcula la rotación de forma aleatoria
//	int r = sdlutils().rand().nextInt(0, 360);
//	asteroide->addComponent<Transform>(p + v.rotate(r) * 2 * w, v.rotate(r) * 1.1f, size, size, 0.0f);
//	// Se podrá dividir una vez menos que su predecesor
//	asteroide->addComponent<Generations>(gen - 1);
//	asteroide->addComponent<ShowAtOppositeSide>();
//	// Si el antiguo asteroide tenia el componente follow el nuevo tambien lo tendra, y ademas habra que usar el sprite dorado
//	if (as->hasComponent<Follow>())
//	{
//		asteroide->addComponent<Follow>();
//		asteroide->addComponent<FramedImage>(&sdlutils().images().at("asteroideOro"), 5, 6, 0, 0);
//	}
//	// Si no lo tenía, al nuevo no se le añade y se usa el sprite de asteroide normal
//	else asteroide->addComponent<FramedImage>(&sdlutils().images().at("asteroide"), 5, 6, 0, 0);
//	asteroide->setGroup<Asteroids>(true);
//	// Se actualiza el numero de asteroides
//	numAsteroides++;
//}
