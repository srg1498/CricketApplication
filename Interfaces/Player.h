#ifndef PLAYER_HPP
#define PLAYER_HPP

#include<string>

class Player{
    public:
           std::string playerName;
           bool canBowl;
           int playerId;
           
           Player(std::string playerName, bool canBowl, int playerId);
           ~Player();

           int getRunsScored();
           int getBallsPlayed();
           int getWickets();
           int getRunsGivenAway();
           int getBallsBowled();
           void updateRunsScored(int runs);
           void updateBallsPlayed();
           void updateWickets();
           void updateRunsGivenAway(int runs);
           void updateBallsBowled();
           void resetBallsBowled();
           
    private:
            int runsScored;
            int ballsPlayed;
            int wickets;
            int runsGivenAway;
            int ballsBowled;
};

#endif