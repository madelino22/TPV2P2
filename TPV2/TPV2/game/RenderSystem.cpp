#include "RenderSystem.h"
#include "../components/Transform.h"
#include "../ecs_4/ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Generations.h"
#include "GameCtrlSystem.h"

RenderSystem::RenderSystem()
{
	tr_ = nullptr;
	entidades = nullptr;

	//las texturas normales estan en un array con un nombre identificativo del enum
	tex_.push_back(&sdlutils().images().at("nave"));
	tex_.push_back(&sdlutils().images().at("asteroide"));
	tex_.push_back(&sdlutils().images().at("asteroideOro"));
	tex_.push_back(&sdlutils().images().at("fire"));
	tex_.push_back(&sdlutils().images().at("heart"));


	//las texturas de texto las hemos separado para distinguirlas de las otras
	NEWGAMEText = &sdlutils().msgs().at("NEWGAME");
	PAUSEDText = &sdlutils().msgs().at("PAUSED");
	WINNERText = &sdlutils().msgs().at("WINNER");
	GAMEOVERText = &sdlutils().msgs().at("GAMEOVER");

	//se comienza con el texto de newgame
	menuText = NEWGAMEText;
	
}

void RenderSystem::renderEntities()
{

	
	//para cada entidad se checkea si es jet, bala o asteroide(normales y de oro), y en función de eso se pinta su textura, preguntando al array de texturas

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
	//recibe l atextura del asteroide, que puede ser de oro o no, pero como las spritesheets son iguales va a funcionar bien
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
void RenderSystem::receive(const Message& m)
{

	//si se ha destruido el caza, en función de las vidas que tenga muestra un texto u otro
	if (m.id_ == JET_DESTROYED)
	{
		health = m.jetDest.lives;
		if (m.jetDest.lives <= 0) menuText = GAMEOVERText;
		else menuText = PAUSEDText;
	}
	else if (m.id_ == ASTEROIDS_DESTROYED)
	{
		//si se ha ganado se muestra el texto de victoria
		menuText = WINNERText;
	}
	else if (m.id_ == STATE_CHANGED && m.state_changed.state == NEWGAME) {
		//si se está en el estado de newgame muestra su texto y reinicia las vidas del hud
		menuText = NEWGAMEText;
		health = 3;
	}

}
void RenderSystem::renderHUD()
{

	//pinta  tantos corazones como vidas tenga
	src_.w = tex_[heart]->width();
	src_.h = tex_[heart]->height();
	Vector2D pos(0, 0);
	SDL_Rect dest = build_sdlrect(pos, 30, 30);
	for (int i = 0; i < health; ++i)
	{
		tex_[heart]->render(src_, dest, 0);
		//Cada vez que pinta uno cambia la posición x del siguiente, dejando un margen
		dest.x = dest.x + dest.w + 5;
	}
}

void RenderSystem::renderMessages()
{
	//al cambiuar de estado cambia el puntero de la variable menuText asique pinta bien el texto
	menuText->render(200, 200);
}

void RenderSystem::update()
{
	
	renderEntities();
	if (manager_->getSystem<GameCtrlSystem>()->getGameState() != RUNNING) renderMessages();
	renderHUD();
	
}
