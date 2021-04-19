#pragma once
#include "../ecs_4/ecs/System.h"
#include "../ecs_4/ecs/Entity.h"
#include "../sdlutils/Texture.h"
#include <vector>

class RenderSystem :
    public System
{
public:
    RenderSystem();
    void renderEntities();// - dibujar asteroides, balas y caza (sólo si el juego no está parado).
    void renderHUD();// - dibujar el marcador y las vidas (siempre).
    void renderMessages();// - dibujar el mensaje correspondiente si el juego está parado (como en la práctica 1)
    void update() override;
    void getEntities(const std::vector<Entity*>* ent) { entidades = ent; }
private:
    Transform* tr_;
    const std::vector<Entity*>* entidades;
    Texture* tex_;
};

