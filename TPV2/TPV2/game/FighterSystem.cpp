#include "FighterSystem.h"
#include "../ecs_4/ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"
#include "../sdlutils/InputHandler.h"
#include "GameCtrlSystem.h"

void FighterSystem::onCollisionWithAsteroid(Entity* a)
{
}

void FighterSystem::init()
{
	//esto iría en el fighterSystem
	Entity* fighter = manager_->addEntity();
	manager_->addComponent<Transform>(fighter, Vector2D(sdlutils().width() / 2, sdlutils().height() / 2), Vector2D(0, 0), 20, 20, 0);
	manager_->setHandler<JET>(fighter);
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
		pos = pos + vel; // Esto lo hacía el update antes del transform
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
