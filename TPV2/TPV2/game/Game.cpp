// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../components/Transform.h"
#include "../ecs_4/ecs/ecs.h"
#include "../ecs_4/ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs_4/ecs/Manager.h"
#include "../utils/Vector2D.h"
#include "RenderSystem.h"
#include "GameCtrlSystem.h"
#include "FighterSystem.h"
#include "BulletsSystem.h"
#include "FighterGunSystem.h"
#include "AsteroidsSystem.h"
#include "CollisionSystem.h"



Game::Game() {
	mngr_.reset(new Manager());
	gameCrtlSystem = nullptr;
	renderSystem = nullptr;
}

Game::~Game() {
}

void Game::init() {

	SDLUtils::init("Asteroids", 800, 600,
			"resources/config/resources.json");





	//auto *ball = mngr_->addEntity();
	//mngr_->addComponent<Transform>(ball, Vector2D(sdlutils().width() / 2.0f, sdlutils().height() / 2.0f),
	//	Vector2D(), 10.0f, 10.0f, 0.0f);
	//mngr_->addComponent<Transform>(ball,
	//		Vector2D(sdlutils().width() / 2.0f, sdlutils().height() / 2.0f),
	//		Vector2D(), 10.0f, 10.0f, 0.0f);

	
	fighterSystem = mngr_->addSystem<FighterSystem>();
	bulletsSystem = mngr_->addSystem<BulletsSystem>();
	fighterGunSystem = mngr_->addSystem<FighterGunSystem>();
	gameCrtlSystem = mngr_->addSystem<GameCtrlSystem>();
	renderSystem = mngr_->addSystem<RenderSystem>();
	asteroidsSystem = mngr_->addSystem<AsteroidsSystem>();
	collisionSystem = mngr_->addSystem<CollisionSystem>();
	
	dynamic_cast<RenderSystem*>(renderSystem)->getEntities(&(mngr_->getEnteties()));
	dynamic_cast<BulletsSystem*>(bulletsSystem)->getEntities(&(mngr_->getEnteties()));
	dynamic_cast<AsteroidsSystem*>(asteroidsSystem)->getEntities(&(mngr_->getEnteties()));
	dynamic_cast<CollisionSystem*>(collisionSystem)->getEntities(&(mngr_->getEnteties()));



	
	//for (int i = 0; i != 5000; ++i) renderSystem->update();


}

void Game::start() {

	/* a boolean to exit the loop*/
	bool exit = false;
	SDL_Event event;

	while (!exit) {
		Uint32 startTime = sdlutils().currRealTime();

		ih().clearState();
		while (SDL_PollEvent(&event))
			ih().update(event);

		if (ih().isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}

		gameCrtlSystem->update();
		fighterSystem->update();
		bulletsSystem->update();
		fighterGunSystem->update();
		asteroidsSystem->update();
		collisionSystem->update();
		//asteroidsSystem->update();
		//mngr_->update();
		mngr_->refresh();

		sdlutils().clearRenderer();
		renderSystem->update();
		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
	}

}

