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
    std::vector<Entity*>* getEntidades() { return &entidades; }
private:
    
    GameState estado = NEWGAME;
    Transform* jetTr;
    std::vector<Entity*> entidades;
    
};

