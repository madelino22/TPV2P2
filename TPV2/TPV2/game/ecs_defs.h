// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../game/messages.h"
// components -- forward declaration, i.e., assume they are defined somewhere
class Transform;
class Generations;


#define _CMPS_LIST_  \
	Transform, Generations\
	

// groups

struct Bullets;
struct Asteroids;
struct JET;
#define _GRPS_LIST_  Bullets, Asteroids, JET

// handlers
struct JET;
#define _HDLRS_LIST_ JET


//systems
class GameCtrlSystem;
class RenderSystem;
class FighterSystem;
class BulletsSystem;
class FighterGunSystem;
class AsteroidsSystem;
class CollisionSystem;
#define _SYS_LIST_ GameCtrlSystem, RenderSystem, FighterSystem, BulletsSystem, FighterGunSystem, AsteroidsSystem,CollisionSystem