#pragma once
#include "../ecs_4/ecs/System.h"
#include "../ecs_4/ecs/Entity.h"
#include <vector>

enum GameState {NEWGAME, PAUSE, RUNNING, GAMEOVER, WON};

class GameCtrlSystem :
    public System
{
public:
    void onFighterDeath(int fighterLives);
    void onAsteroidsExtinction();
    GameState getGameState();
    void init() override;
    void update() override;
    void getEntities(const std::vector<Entity*>* ent) { entidades = ent; }
    virtual void receive(const Message& m);
private:
    
    GameState estado = NEWGAME;
    Transform* jetTr;
    const std::vector<Entity*>* entidades;

};

