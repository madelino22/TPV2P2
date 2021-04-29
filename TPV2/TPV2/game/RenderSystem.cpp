#include "RenderSystem.h"
#include "../components/Transform.h"
#include "../ecs_4/ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Generations.h"

RenderSystem::RenderSystem()
{
	tr_ = nullptr;
	entidades = nullptr;
	tex_ = nullptr;
}

void RenderSystem::renderEntities()
{
	for (Entity* e : *entidades)
	{
		tr_ = manager_->getComponent<Transform>(e);
		SDL_Rect dest = build_sdlrect(tr_->getPos(), tr_->getW(), tr_->getH()); // Rectangulo destino donde se va a dibujar el objeto en pantalla

		 if(manager_->getHandler<JET>() == e) tex_ = &sdlutils().images().at("nave");
		 else if (manager_->hasGroup<Asteroids>(e)) {
			
			 if(manager_->getComponent<Generations>(e)->isGold())
				 tex_ = &sdlutils().images().at("asteroideOro");
			 else
				 tex_ = &sdlutils().images().at("asteroide");

		 }
		 else if (manager_->hasGroup<Bullets>(e)) tex_ = &sdlutils().images().at("fire");


		SDL_Rect src_ = { 0,0, tex_->width(), tex_->height() };
		tex_->render(src_, dest, tr_->getRot());
	}
}

void RenderSystem::renderHUD()
{

}

void RenderSystem::renderMessages()
{
}

void RenderSystem::update()
{
	// if (state == RUNNING)
	renderEntities();
	///*else*/ renderMessages();
	//renderHUD();
	
}
