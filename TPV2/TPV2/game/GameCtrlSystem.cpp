#include "GameCtrlSystem.h"
#include "../ecs_4/ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"
#include "../sdlutils/InputHandler.h"
#include "AsteroidsSystem.h"


void GameCtrlSystem::onFighterDeath(int fighterLives)
{

	for (Entity* e : *entidades) {
		if (manager_->hasGroup<Bullets>(e) ) {
			manager_->setActive(e, false);
		}
		if (manager_->hasGroup<Asteroids>(e)) {
			manager_->setActive(e, false);
		}
	}
	
	//sonido
	sdlutils().soundEffects().at("bangSmall").play();

	
	//si se lanza el estado de ganar aqui se cambia al corresponiente
	if (fighterLives > 0) estado = PAUSE;
	else estado = GAMEOVER;

	Message cambioDeEstado;
	cambioDeEstado.id_ = STATE_CHANGED;
	cambioDeEstado.state_changed.state = estado;
	manager_->send(cambioDeEstado);


	//Desactivar movimiento y armas
	
}

void GameCtrlSystem::onAsteroidsExtinction()
{
	for (Entity* e : *entidades) {
		if (manager_->hasGroup<Bullets>(e)) {
			manager_->setActive(e, false);
		}
		
	}


	jetTr->setRot(0.0f);
	jetTr->setVel(Vector2D(0, 0));
	jetTr->setPos(Vector2D(sdlutils().width() / 2.0f, sdlutils().height() / 2.0f));

	estado = WON;

	Message cambioDeEstado;
	cambioDeEstado.id_ = STATE_CHANGED;
	cambioDeEstado.state_changed.state = estado;
	manager_->send(cambioDeEstado);
}

GameState GameCtrlSystem::getGameState()
{
	return estado;
}

void GameCtrlSystem::init()
{
	//estado = NEWGAME;

	jetTr = manager_->getComponent<Transform>(manager_->getHandler<JET>());
	


}

void GameCtrlSystem::update()
{

	
	if (ih().keyDownEvent()) {
		// Al pulsar la tecla espacio se actualiza el estado actual
		if (ih().isKeyDown(SDL_SCANCODE_SPACE)) {

			

			//si se está en un estado distinto de running, es decir en un menú, y se ha pulsado espacio
			if (estado != RUNNING)
			{
				if (estado == GAMEOVER || estado == WON)
				{
					//al ganar o perder hay que poner las vidas como al principio de la partida
					//-------->Resetear vidas en jetsystem
					//una vez restablecidos los valor se cambia el estado a pausa
					estado = NEWGAME;
				}
				else
				{
					// Si el estado es NEWGAME o PAUSED habrá que añadir los componentes de accion al caza para que se pueda volver a jugar
					//--------->activar movimiento y armas
					// Ademas, generamos los diez asteroides iniciales
					
					manager_->getSystem<AsteroidsSystem>()->addAsteroids(2);

					// Pasamos a RUNNING
					estado = RUNNING;
				}

				Message cambioDeEstado;
				cambioDeEstado.id_ = STATE_CHANGED;
				cambioDeEstado.state_changed.state = estado;
				manager_->send(cambioDeEstado);
			}


		}
	}


}

void GameCtrlSystem::receive(const Message& m)
{
	if (m.id_ == JET_DESTROYED)
		onFighterDeath(m.jetDest.lives);
	else if (m.id_ == ASTEROIDS_DESTROYED)
	{
		onAsteroidsExtinction();
	}
	
}
