#include "RenderSystem.h"
#include "../components/Transform.h"
#include "../ecs_4/ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Generations.h"

RenderSystem::RenderSystem()
{
	tr_ = nullptr;
	entidades = nullptr;
	tex_.push_back(&sdlutils().images().at("nave"));
	tex_.push_back(&sdlutils().images().at("asteroide"));
	tex_.push_back(&sdlutils().images().at("asteroideOro"));
	tex_.push_back(&sdlutils().images().at("fire"));
}

void RenderSystem::renderEntities()
{
	for (Entity* e : *entidades)
	{
		 tr_ = manager_->getComponent<Transform>(e);
		 SDL_Rect dest = build_sdlrect(tr_->getPos(), tr_->getW(), tr_->getH()); // Rectangulo destino donde se va a dibujar el objeto en pantalla
		 if (manager_->hasGroup<JET>(e))
		 {
			 src_ = { 0,0, tex_[nave]->width(), tex_[nave]->height() };
			 tex_[nave]->render(src_, dest, tr_->getRot());
		 }
		 else if (manager_->hasGroup<Bullets>(e))
		 {
			 src_ = { 0,0, tex_[bala]->width(), tex_[bala]->height() };
			 tex_[bala]->render(src_, dest, tr_->getRot());
		 }
		 else if (manager_->hasGroup<Asteroids>(e))
		 {		 
			 if (manager_->getComponent<Generations>(e)->isGold())
			 {
				 renderAsteroid(tex_[asteroide_oro],dest);
			 }
			 else
			 {
				 renderAsteroid(tex_[asteroide],dest);
			 }
		 }
	}
}

void RenderSystem::renderAsteroid(Texture* tex_, SDL_Rect dest)
{
	src_asteroids.w = tex_->width()/6;
	src_asteroids.h = tex_->height()/5;
	if (sdlutils().currRealTime() >= timer + 50) // Cada 50 ms debe cambiar el fragmento que cogemos de la textura
	{
		src_asteroids.x = src_asteroids.x + src_asteroids.w; // A la posición horizontal en la que estamos de la textura le sumamos el ancho de la imagen para que pasemos a la siguiente imagen del spritesheet
		if (src_asteroids.x >= tex_->width()) // Si al hacerlo superamos el ancho del spritesheet, pasamos a la siguiente fila empezando por la izquierda
		{
			src_asteroids.x = 0;
			src_asteroids.y = src_asteroids.y + src_asteroids.h;
		}
		if (src_asteroids.y >= tex_->height()) // Si superamos el alto del spritesheet, volvemos a empezar desde el principio
		{
			src_asteroids.y = 0;
		}
		timer = sdlutils().currRealTime(); // Actualizamos el contador 
		frameTexture++;
	}
	tex_->render(src_asteroids, dest, tr_->getRot());
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
