// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_stdinc.h>

//#include "GameManagerSystem.h"

enum MsgId : Uint8 {
	_BALL_EXIT, _ROUND_START, _ROUND_OVER, _GAME_OVER
};

struct BallExitMsg {
	//GameManagerSystem::Side side_;
};

struct SomeOtherMsg { // just for the example
	int otherData_;
};

struct Message {
	MsgId id_;
	union {
		BallExitMsg ballExit_;
		SomeOtherMsg otherMsg_; // just for the example
	};
};
