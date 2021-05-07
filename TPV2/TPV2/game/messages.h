// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_stdinc.h>

//#include "GameManagerSystem.h"
class Entity;
enum MsgId : Uint8 {
	ASTEROIDS_DESTROYED, JET_DESTROYED, JET_COLLISION_WITH_ASTEROID, ASTEROID_COLLISION_WITH_BULLET, STATE_CHANGED
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

struct ROUND_OVER_MESSAGE {
};


enum GameState;
struct STATE_CHANGED_MESSAGE{
	GameState state;
};
 

struct Message {
	MsgId id_;
	union {
		JET_DESTROYED_MESSAGE jetDest;
		JET_COLLISION_WITH_ASTEROID_MESSAGE jetCol;
		ASTEROID_COLLISION_WITH_BULLET_MESSAGE entitiesCol;
		ASTEROIDS_DESTROYED_MESSAGE a;
		ROUND_OVER_MESSAGE round_over;
		STATE_CHANGED_MESSAGE state_changed;
		//SomeOtherMsg otherMsg_; // just for the example
	};
};
