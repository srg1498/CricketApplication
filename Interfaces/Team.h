#ifndef TEAM_HPP
#define TEAM_HPP

#include<vector>
#include<string>
#include<map>
#include "./Player.h"


class Team{
    public:
           std::string teamName;
           std::vector<Player> players;
           std::vector<int> bowlersIDs;
           int teamId;
           
           Team(std::string teamName, int teamId, std::map<std::string, std::string> playersInfo);
           ~Team();
           
           int getTeamruns();
           int getTeamWickets();
           void updateTeamRuns(int runs);
           void updateTeamWickets();
           void resetTeamRuns();
           void resetTeamWickets();

    private:
            int teamRuns;
            int teamWickets;
};

#endif