#ifndef GAME_HPP
#define GAME_HPP

#include<map>
#include<string>
#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
#include "./Team.h"
#include "../FileHandler/FileReader.h"
#include "../FileHandler/FileWriter.h"


class Game{
    public:
           ~Game();

           static Game* loadGame();
           void tossTime();
           void startGame();
           bool isMatchTied();
           void startSuperOver();
           void showSummary();

    private:
           static Game* instance;
           std::vector<Team> teams;
           std::map<std::string, std::map<std::string, std::map<std::string, std::string>>> outcomesOnBowlCard;
           std::map<std::string, std::map<std::string, std::string>> allTeamsInfo;
           std::map<std::string, std::vector<std::string>> commentary;
           std::vector<std::string> bowlCards;
           std::vector<std::string> shots;
           std::vector<std::string> timings;
           int teamBattingFirstId;
           int teamBowlingFirstId;
           bool matchTied;
           FileWriter* summaryWriter;
           FileWriter* commentaryWriter;

           Game();

           void loadShotOutcomes(std::string filePath);
           void loadTeamsInfo(std::string filePath);
           void loadCommentary(std::string filePath);
           void createTeams();
           void loadInput(std::string inputFilePath, int maxOvers, int noOfTeams);
           int getBowlerForNewOver(std::vector<int>& bowlersIds, int lastBowlerId, int teamBowlingFirstId, int maxOversBowlerCanBowl, int maxBallsBowlerCanBowlInOneOver);
           std::string getOutcomeOnBall(FileReader& obj, int teamBattingId, int teamBowlingId, int batterId, int bowlerId, std::string& overSummary);
           void startInnings(int teamBattingId, int teamBowlingId, FileReader& obj, int maxOvers, int maxWkts, int maxOversBowlerCanBowl, int maxBallsInOneOver, int target);
           void updateSummaryOfOneInnings(int teamBattingId, int teamBowlingId);
           void updateSummary();
};

#endif