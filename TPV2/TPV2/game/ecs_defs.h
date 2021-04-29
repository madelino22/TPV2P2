// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

// components -- forward declaration, i.e., assume they are defined somewhere
class Transform;
class Generations;


#define _CMPS_LIST_  \
	Transform, Generations\
	

// groups

struct Bullets;
struct Asteroids;
#define _GRPS_LIST_  Bullets, Asteroids

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
#define _SYS_LIST_ GameCtrlSystem, RenderSystem, FighterSystem, BulletsSystem, FighterGunSystem, AsteroidsSystem