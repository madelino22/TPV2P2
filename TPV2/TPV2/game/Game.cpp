// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../components/Transform.h"
#include "../ecs_4/ecs/ecs.h"
#include "../ecs_4/ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include "../ecs_4/ecs/Manager.h"
#include "../utils/Vector2D.h"

Game::Game() {
	mngr_.reset(new Manager());
}

Game::~Game() {
}

void Game::init() {

	SDLUtils::init("Asteroids", 800, 600,
			"resources/config/resources.json");





	/*auto *ball = mngr_->addEntity();
	mngr_->addComponent<Transform>(ball, Vector2D(sdlutils().width() / 2.0f, sdlutils().height() / 2.0f),
		Vector2D(), 10.0f, 10.0f, 0.0f);*/
	/*ball->addComponent<Transform>(
			Vector2D(sdlutils().width() / 2.0f, sdlutils().height() / 2.0f),
			Vector2D(), 10.0f, 10.0f, 0.0f);*/
	


}

void Game::start() {

	// a boolean to exit the loop
	//bool exit = false;
	//SDL_Event event;

	//while (!exit) {
	//	Uint32 startTime = sdlutils().currRealTime();

	//	ih().clearState();
	//	while (SDL_PollEvent(&event))
	//		ih().update(event);

	//	if (ih().isKeyDown(SDL_SCANCODE_ESCAPE)) {
	//		exit = true;
	//		continue;
	//	}

	//	//mngr_->update();
	//	mngr_->refresh();

	//	sdlutils().clearRenderer();
	//	//mngr_->render();
	//	sdlutils().presentRenderer();

	//	Uint32 frameTime = sdlutils().currRealTime() - startTime;

	//	if (frameTime < 20)
	//		SDL_Delay(20 - frameTime);
	//}

}

