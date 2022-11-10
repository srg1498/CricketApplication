#include<iostream>
#include<string>
#include<vector>
#include<map>
#include "./Interfaces/Game.h"

int main(){

    Game* game = Game::loadGame();
    
    game->tossTime();
    
    game->startGame();
    
    if(game->isMatchTied())
        game->startSuperOver();

    game->showSummary();
    
    delete game;
    
    return 0;
}