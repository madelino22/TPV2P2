#pragma once
#include "../ecs_4/ecs/System.h"
#include "../ecs_4/ecs/Entity.h"
#include "../sdlutils/Texture.h"
#include <vector>
enum texturas {nave,asteroide,asteroide_oro,bala, heart};
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
    void renderAsteroid(Texture* tex_, SDL_Rect dest);
    virtual void receive(const Message& m);

private:
    Transform* tr_;
    const std::vector<Entity*>* entidades;
    std::vector<Texture*> tex_;
    float timer = 0;
    SDL_Rect src_;
    SDL_Rect src_asteroids;
    int frameTexture = 0;
    Texture* NEWGAMEText;
    Texture* PAUSEDText;
    Texture* WINNERText;
    Texture* GAMEOVERText;
    Texture* menuText;
    int health = 3;
};

