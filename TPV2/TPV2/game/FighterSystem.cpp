#include "FighterSystem.h"
#include "../ecs_4/ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"
#include "../sdlutils/InputHandler.h"
#include "GameCtrlSystem.h"

void FighterSystem::onCollisionWithAsteroid(Entity* a)
{
	// El jugador pierde una vida
	lives--;

	// El caza vuelve al centro de la pantalla con velocidad nula y orientado hacia arriba
	tr->setRot(0.0f);
	tr->setVel(Vector2D(0, 0));
	tr->setPos(Vector2D(sdlutils().width() / 2.0f, sdlutils().height() / 2.0f));
	// Se eliminan los componentes de accion del caza para que no se pueda mover ni disparar hasta que comience la partida
	
	Message jet_destroyed;
	jet_destroyed.id_ = JET_DESTROYED;
	jet_destroyed.jetDest.lives = lives;
	manager_->send(jet_destroyed);
	
	
	


	manager_->setActive(a, false);
}





void FighterSystem::init()
{
	//esto iría en el fighterSystem
	Entity* fighter = manager_->addEntity();
	manager_->addComponent<Transform>(fighter, Vector2D(sdlutils().width() / 2, sdlutils().height() / 2), Vector2D(0, 0), 20, 20, 0);
	manager_->setHandler<JET>(fighter);
	manager_->setGroup<JET>(fighter,true);
	tr = manager_->getComponent<Transform>(fighter);
	bulletsSystem = manager_->getSystem<BulletsSystem>();
}
void FighterSystem::update()
{
	if (manager_->getSystem<GameCtrlSystem>()->getGameState() == RUNNING)
	{
		auto& pos = tr->getPos();
		auto& vel = tr->getVel();
		auto r = tr->getRot();
		auto w = tr->getW();
		auto h = tr->getH();
		pos = pos + vel; // Esto lo hacía el update antes del transform
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
		if (ih().keyDownEvent()) {

			//Si se presiona la s, acelera
			if (ih().isKeyDown(SDL_SCANCODE_UP)) {

				Vector2D newVel;
				r = tr->getRot();
				auto& vel = tr->getVel();
				//se acelera en la dirección en la que se es´ta mirando por lo que
				//hay que tener en cuenta  la rotación
				newVel = vel + Vector2D(0, -1).rotate(r) * thrust;

				//limitador de velocidad
				if (newVel.magnitude() > speedLimit)
					newVel = newVel.normalize() * speedLimit;


				(vel).setX(newVel.getX());
				(vel).setY(newVel.getY());

				//además, al acelerar se reproduce un sonido
				sdlutils().soundEffects().at("thrust").play();

			}


			//si se gira izquierda o derecha se rota la nave
			if (ih().isKeyDown(SDL_SCANCODE_LEFT)) {
				tr->setRot(tr->getRot() - 5.0f);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_RIGHT)) {
				tr->setRot(tr->getRot() + 5.0f);
			}
			
		}
		vel = vel * 0.995f;
	}
}

void FighterSystem::receive(const Message& m)
{
	if (m.id_ == JET_COLLISION_WITH_ASTEROID) onCollisionWithAsteroid(m.jetCol.entity);
	else if (m.id_ == STATE_CHANGED) {
		if (m.state_changed.state == NEWGAME) lives = 3;
	}
}
