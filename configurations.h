#ifndef CONFIGURATIONS_HPP
#define CONFIGURATIONS_HPP
#include<string>

namespace PATH_VARIABLES{
    std::string SHOTOUTCOMES_PATH = "./MediaFiles/ShotOutcomes/";
    std::string TEAMS_PATH = "./MediaFiles/Teams/";
    std::string COMMENTARY_PATH = "./MediaFiles/Commentary/";

    std::string GAME_INPUT_FILEPATH = "./InputsAndOutputs/Inputs/GameInput.txt";
    std::string GAME_SUPER_OVER_INPUT_FILEPATH = "./InputsAndOutputs/Inputs/GameSuperOverInput.txt";
    
    std::string GAME_COMMENTARY_FILEPATH = "./InputsAndOutputs/Outputs/GameCommentary.txt";
    std::string MATCH_SUMMARY_FILEPATH = "./InputsAndOutputs/Outputs/MatchSummary.txt";
};

namespace CRIC_VARIABLES{
    int MAX_OVERS = 20;
    int SUPEROVERS = 1;

    int NO_OF_TEAMS = 2;
    
    int MAX_WKTS = 10;
    int MAX_WKTS_IN_SUPEROVER = 2;
    
    int MAX_OVERS_BOWLER_CAN_BOWL = 4;
    int MAX_OVERS_BOWLER_CAN_BOWL_IN_SUPEROVER = 1;
    
    int MAX_BALLS_IN_ONE_OVER = 6;
};

#endif