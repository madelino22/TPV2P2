#include "RenderSystem.h"
#include "../components/Transform.h"
#include "../ecs_4/ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"

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
		tex_ = &sdlutils().images().at("Asteroid");
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
