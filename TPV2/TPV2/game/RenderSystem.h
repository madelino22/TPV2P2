#pragma once
#include "../TPV2/ecs_4/ecs/System.h"
#include "../TPV2/ecs_4/ecs/Entity.h"
#include "sdlutils/Texture.h"
#include <vector>

class RenderSystem :
    public System
{
public:
    RenderSystem(std::vector<Entity*>* entidades_);
    void renderEntities();// - dibujar asteroides, balas y caza (sólo si el juego no está parado).
    void renderHUD();// - dibujar el marcador y las vidas (siempre).
    void renderMessages();// - dibujar el mensaje correspondiente si el juego está parado (como en la práctica 1)
    void update() override;

private:
    Transform* tr_;
    std::vector<Entity*>* entidades;
    Texture* tex_;
};

