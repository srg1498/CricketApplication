#include "../Interfaces/Player.h"
#include<iostream>
#include<string>


Player::Player(std::string playerName, bool canBowl, int playerId) : playerName(playerName), playerId(playerId), canBowl(canBowl), runsScored(0), ballsPlayed(0), wickets(0), runsGivenAway(0), ballsBowled(0){
    //std::cout<<"player object constructed\n";
}


Player::~Player(){
    //std::cout<<"player object destructed\n";
}


int Player::getRunsScored(){
    return runsScored;
}


int Player::getBallsPlayed(){
    return ballsPlayed;
}


int Player::getWickets(){
    return wickets;
}


int Player::getRunsGivenAway(){
    return runsGivenAway;
}


int Player::getBallsBowled(){
    return ballsBowled;
}


void Player::updateRunsScored(int runs){
    runsScored += runs;
}


void Player::updateBallsPlayed(){
    ballsPlayed++;
}


void Player::updateWickets(){
    wickets++;
}


void Player::updateRunsGivenAway(int runs){
    runsGivenAway += runs;
}


void Player::updateBallsBowled(){
    ballsBowled++;
}


void Player::resetBallsBowled(){
    ballsBowled = 0;
}