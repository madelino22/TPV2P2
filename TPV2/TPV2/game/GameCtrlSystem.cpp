#include "GameCtrlSystem.h"
#include "../ecs_4/ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"
#include "../sdlutils/InputHandler.h"
#include "AsteroidsSystem.h"


//cuando el jet muere se encarga de desactivar todas las balas y asteroides, se llama a este método al recibir un mensaje
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


	//como cambia el estado lanza  el mensaje de estado cambiado
	Message cambioDeEstado;
	cambioDeEstado.id_ = STATE_CHANGED;
	cambioDeEstado.state_changed.state = estado;
	manager_->send(cambioDeEstado);

	
}


void GameCtrlSystem::onAsteroidsExtinction()
{

	//al acabarse todos los asteroides se gana y se desactivan todas las balas y se resetea al jet

	for (Entity* e : *entidades) {
		if (manager_->hasGroup<Bullets>(e)) {
			manager_->setActive(e, false);
		}
		
	}


	jetTr->setRot(0.0f);
	jetTr->setVel(Vector2D(0, 0));
	jetTr->setPos(Vector2D(sdlutils().width() / 2.0f, sdlutils().height() / 2.0f));


	//como cambia el estado lanza  el mensaje de estado cambiado
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
	
	//recibe el transform del jet para tenerle mejor controlado
	jetTr = manager_->getComponent<Transform>(manager_->getHandler<JET>());
	


}

void GameCtrlSystem::update()
{

	//Recoge el input de teclado para el cambio de estado
	if (ih().keyDownEvent()) {
		// Al pulsar la tecla espacio se actualiza el estado actual
		if (ih().isKeyDown(SDL_SCANCODE_SPACE)) {

			

			//si se está en un estado distinto de running, es decir en un menú, y se ha pulsado espacio
			if (estado != RUNNING)
			{
				if (estado == GAMEOVER || estado == WON)
				{
					estado = NEWGAME;
				}
				else
				{
					
					// Generamos los diez asteroides iniciales
					
					manager_->getSystem<AsteroidsSystem>()->addAsteroids(10);

					// Pasamos a RUNNING
					estado = RUNNING;
				}



				//como cambia el estado lanza  el mensaje de estado cambiado
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

	//Se pueden recibir dos mensajes, la muerte del jet, que si es la tercera llevará al estado newgame, si no al pause, y 
	//el de la destrucción de todo slos asteroides que lleva al estado won
	if (m.id_ == JET_DESTROYED)
		onFighterDeath(m.jetDest.lives);
	else if (m.id_ == ASTEROIDS_DESTROYED)
	{
		onAsteroidsExtinction();
	}
	
}
