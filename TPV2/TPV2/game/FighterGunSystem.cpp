#include "FighterGunSystem.h"
#include "GameCtrlSystem.h"
#include "../ecs_4/ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
void FighterGunSystem::init()
{
	tr = manager_->getComponent<Transform>(manager_->getHandler<JET>());
}
void FighterGunSystem::update()
{
	if (manager_->getSystem<GameCtrlSystem>()->getGameState() == RUNNING)
	{
		auto& pos = tr->getPos();
		auto& vel = tr->getVel();
		auto r = tr->getRot();
		if (ih().keyDownEvent()) {

			//Si se presiona la s, acelera
			if (ih().isKeyDown(SDL_SCANCODE_UP)) {
				if (ih().isKeyDown(SDLK_s) && sdlutils().currRealTime() >= timer + 250) {
					timer = sdlutils().currRealTime();
					bulletsSystem->shoot(pos, vel, 50, 50);
				}
			}
		}
	}
}