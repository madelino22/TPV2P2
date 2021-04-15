#pragma once
#include "../TPV2/ecs_4/ecs/System.h"
#include "../TPV2/ecs_4/ecs/Entity.h"
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
    
private:
    
    GameState estado = NEWGAME;
    Transform* jetTr;
    std::vector<Entity*> entidades;
    
};

