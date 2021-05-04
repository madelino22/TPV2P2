// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_stdinc.h>

//#include "GameManagerSystem.h"
class Entity;
enum MsgId : Uint8 {
	ASTEROIDS_DESTROYED, JET_DESTROYED, _ROUND_OVER, _GAME_OVER, JET_COLLISION_WITH_ASTEROID, ASTEROID_COLLISION_WITH_BULLET
};

struct ASTEROIDS_DESTROYED_MESSAGE {
	//GameManagerSystem::Side side_;
};
struct JET_DESTROYED_MESSAGE {
	int lives;
};

struct JET_COLLISION_WITH_ASTEROID_MESSAGE {
	//GameManagerSystem::Side side_;
	Entity* entity;
};
struct ASTEROID_COLLISION_WITH_BULLET_MESSAGE {
	Entity* bullet;
	Entity* asteroid;
};
struct Message {
	MsgId id_;
	union {
		JET_DESTROYED_MESSAGE jetDest;
		JET_COLLISION_WITH_ASTEROID_MESSAGE jetCol;
		ASTEROID_COLLISION_WITH_BULLET_MESSAGE entitiesCol;
		ASTEROIDS_DESTROYED_MESSAGE a;
		//SomeOtherMsg otherMsg_; // just for the example
	};
};
