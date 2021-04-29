// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs_4/ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs_4/ecs/Entity.h"
#include "Transform.h"

class Generations : public Component {
public:

	Generations() :
		generations(sdlutils().rand().nextInt(1, 3)) // Se calcula de forma aleatoria el número de divisiones, que puede ser 1, 2 o 3
	{}
	Generations(int g) :
		generations(g)
	{}

	virtual ~Generations() {
	}
	
	bool isGold() { return isGoldBool; };
	void setGold() { isGoldBool = true; }

	int getGenerations()
	{
		return generations;
	}

private:
	int generations; // Numero de veces que se puede dividir un asteroide
	bool isGoldBool = false;
};

