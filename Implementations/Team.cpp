#include "../Interfaces/Team.h"
#include<iostream>
#include<string>
#include<map>


Team::Team(std::string teamName, int teamId, std::map<std::string, std::string> playersInfo) : teamName(teamName), teamId(teamId), teamRuns(0), teamWickets(0){
    //std::cout<<"team object constructed\n";
    int playerId = 0;
    for(auto& playerInfo : playersInfo){
        std::string playerName = playerInfo.first;
        bool canBowl = (playerInfo.second == "yes") ? true : false;
        Player pl = Player(playerName, canBowl, playerId);
        this->players.push_back(pl);
        if(canBowl)
            this->bowlersIDs.push_back(playerId);
        playerId++;
    }
}


Team::~Team(){
    //std::cout<<"team object destructed\n";
}


int Team::getTeamruns(){
    return teamRuns;
}


int Team::getTeamWickets(){
    return teamWickets;
}


void Team::updateTeamRuns(int runs){
    teamRuns += runs;
}


void Team::updateTeamWickets(){
    teamWickets++;
}


void Team::resetTeamRuns(){
    teamRuns = 0;
}


void Team::resetTeamWickets(){
    teamWickets = 0;
}

