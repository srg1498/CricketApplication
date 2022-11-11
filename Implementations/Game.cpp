#include "../Interfaces/Game.h"
#include "../configurations.h"
#include "../Interfaces/utilityModules.h"
#include "../Interfaces/ShotOutcomesMediaFolderLoader.h"
#include "../Interfaces/TeamsMediaFolderLoader.h"
#include "../Interfaces/CommentaryMediaFolderLoader.h"
#include "../Interfaces/GameInputLineStructure.h"
#include<iostream>


Game* Game::instance = NULL;


Game::Game() : matchTied(false) {
    //std::cout<<"game object constructed\n";
    summaryWriter = new FileWriter(PATH_VARIABLES::MATCH_SUMMARY_FILEPATH);
    commentaryWriter = new FileWriter(PATH_VARIABLES::GAME_COMMENTARY_FILEPATH);
}


Game::~Game(){
    //std::cout<<"game object destrcuted\n";
    delete commentaryWriter;
    instance = NULL;
}


// loads shot outcomes media folder into outcomesOnBowlCard dictionary
void Game::loadShotOutcomes(std::string filePath){
    ShotOutcomesMediaFolderLoader somfl = ShotOutcomesMediaFolderLoader(filePath);
    somfl.loadResDictionary();
    instance->outcomesOnBowlCard = somfl.getResDictionary();
    std::set<std::string> bowlCards, shots, timings;
    for(auto& bowlCard : instance->outcomesOnBowlCard){
        bowlCards.insert(bowlCard.first);
        for(auto& shot : bowlCard.second){
            shots.insert(shot.first);
            for(auto& timing : shot.second){
                timings.insert(timing.first);
            }
        }
    }
    instance->bowlCards = std::vector(bowlCards.begin(), bowlCards.end());
    instance->shots = std::vector(shots.begin(), shots.end());
    instance->timings = std::vector(timings.begin(), timings.end());
}


// loads teams info into dictionary
void Game::loadTeamsInfo(std::string filePath){
    TeamsMediaFolderLoader tmfl = TeamsMediaFolderLoader(filePath);
    tmfl.loadResDictionary();
    instance->allTeamsInfo = tmfl.getResDictionary();
}


// loads commentary into dictionary
void Game::loadCommentary(std::string filePath){
    CommentaryMediaFolderLoader cmfl = CommentaryMediaFolderLoader(filePath);
    cmfl.loadResDictionary();
    instance->commentary = cmfl.getResDictionary();
}
           

// it creates teams 
void Game::createTeams(){
    int teamId = 0; 
    for(auto& team : allTeamsInfo){
        std::string teamName = team.first;
        std::map<std::string, std::string> playersInfo = team.second;
        instance->teams.push_back({teamName, teamId, playersInfo});
        teamId++;
    }
}


// it generates games input if input data is not present in input file
void Game::loadInput(std::string inputFilePath, int maxOvers, int noOfTeams){
    FileReader obj = FileReader(inputFilePath);
    if(obj.isFileEmpty()){
        inputGenerator(inputFilePath, maxOvers, noOfTeams, bowlCards, shots, timings);
    }
}


Game* Game::loadGame(){
    if(instance == NULL){
        std::cout<<"loading all the media files and game input\n\n";
        instance = new Game();
        instance->loadShotOutcomes(PATH_VARIABLES::SHOTOUTCOMES_PATH);
        instance->loadTeamsInfo(PATH_VARIABLES::TEAMS_PATH);
        instance->loadCommentary(PATH_VARIABLES::COMMENTARY_PATH);
        instance->createTeams();
        instance->loadInput(PATH_VARIABLES::GAME_INPUT_FILEPATH, CRIC_VARIABLES::MAX_OVERS, CRIC_VARIABLES::NO_OF_TEAMS);
    }
    return instance;
}


void Game::tossTime(){
    std::cout<<"Toss time now...Hit enter to continue\n\n";
    std::cin.ignore();
    std::vector<std::string> options = {"bat", "bowl"};
    std::vector<int> teamIds = {0, 1};
    srand(time(NULL));
    int randomOption = rand()%2, randomId = rand()%2;
    std::string tossResult = instance->teams[randomId].teamName + " has won the toss and decided to " + options[randomOption] + " first\n";
    if(options[randomOption] == "bat"){
        if(randomId == 0)
            instance->teamBattingFirstId = 0, instance->teamBowlingFirstId = 1;
        else
            instance->teamBattingFirstId = 1, instance->teamBowlingFirstId = 0;
    }else{
        if(randomId == 0)
            instance->teamBattingFirstId = 1, instance->teamBowlingFirstId = 0;
        else
            instance->teamBattingFirstId = 0, instance->teamBowlingFirstId = 1;
    }

    std::cout<<tossResult;
    instance->summaryWriter->appendNextLine(tossResult+"\n");
    instance->commentaryWriter->appendNextLine(tossResult+"\n");
}


int Game::getBowlerForNewOver(std::vector<int>& bowlersIds, int lastBowlerId, int teamBowlingFirstId, int maxOversBowlerCanBowl, int maxBallsBowlerCanBowlInOneOver){
    std::vector<int> :: iterator pos = std::find(bowlersIds.begin(), bowlersIds.end(), lastBowlerId);
    if(pos != bowlersIds.end())
        bowlersIds.erase(pos);
    
    if(bowlersIds.size() == 0){
        std::cout<<teams[teamBowlingFirstId].teamName<<" has not enough bowlers in their team...Please add more bowlers in the team\n\n";
        exit(0);
    }

    srand(time(NULL));       
    int randomBowler = rand()%(bowlersIds.size());
    int resId = bowlersIds[randomBowler];
               
    if((lastBowlerId != -1) && (instance->teams[teamBowlingFirstId].players[lastBowlerId].getBallsBowled() < maxOversBowlerCanBowl*maxBallsBowlerCanBowlInOneOver)){
        bowlersIds.push_back(lastBowlerId);                       
    }

    return resId;
}


std::string Game::getOutcomeOnBall(FileReader& obj, int teamBattingId, int teamBowlingId, int batterId, int bowlerId, std::string& overSummary){
    std::string line = obj.getNextLine();
    std::string commentaryLine;           

    try{
        if(line == ""){
            throw "error while reading the input file";
        }
    }catch(const char* error){
        std::cout<<error<<"\n";
        exit(0);
    }

    std::vector<std::string> words = stringSplit(line, ' ');
    try{
        if(words.size() != CODE_VARIABLES::INPUT_WORD_TO_INTEGER.size())
            throw "error while reading the file...game input for this ball is not mentioned correctly.";
    }catch(const char* error){
        std::cout<<error<<"\n\n";
        exit(0);
    }

    GameInputLineStructure inp = GameInputLineStructure(words[CODE_VARIABLES::INPUT_WORD_TO_INTEGER["BOWLCARD"]],
                                                        words[CODE_VARIABLES::INPUT_WORD_TO_INTEGER["SHOT"]],
                                                        words[CODE_VARIABLES::INPUT_WORD_TO_INTEGER["TIMING"]]);

    // std::string bowlCard = words[0];
    // toLowerCase(bowlCard);
    // std::string shot = words[1];
    // toLowerCase(shot);
    // std::string timing = words[2];
    // toLowerCase(timing);
    
    commentaryLine = "   " + instance->teams[teamBowlingId].players[bowlerId].playerName + " bowls " + inp.getBowlCard() + " to " + instance->teams[teamBattingId].players[batterId].playerName + "\n";
    overSummary = overSummary + commentaryLine;
    instance->commentaryWriter->appendNextLine(commentaryLine);

    commentaryLine = "   " + instance->teams[teamBattingId].players[batterId].playerName + " tries to play " + inp.getShot() + " shot " + "\n";
    overSummary = overSummary + commentaryLine;
    instance->commentaryWriter->appendNextLine(commentaryLine);
    
    try{
        if(outcomesOnBowlCard.find(inp.getBowlCard()) == outcomesOnBowlCard.end()){
            throw "error while reading the input file...bowlcard mentioned in the input file is not correct";
        }else{
            try{
                if(outcomesOnBowlCard[inp.getBowlCard()].find(inp.getShot()) == outcomesOnBowlCard[inp.getBowlCard()].end()){
                    throw "error while reading the input file...shot mentioned in the input file is not correct";    
                }else{
                    try{
                        if(outcomesOnBowlCard[inp.getBowlCard()][inp.getShot()].find(inp.getTiming()) == outcomesOnBowlCard[inp.getBowlCard()][inp.getShot()].end()){
                            throw "error while reading the file...timing mentioned in the input file is not correct";
                        }
                    }catch(const char* error){
                        std::cout<<error<<"\n";
                        exit(0);
                    } 
                }
            }catch(const char* error){
                std::cout<<error<<"\n";
                exit(0);
            }
        }
    }catch(const char* error){
        std::cout<<error<<"\n";
        exit(0);
    }

    std::vector<std::string> outcomes = stringSplit(outcomesOnBowlCard[inp.getBowlCard()][inp.getShot()][inp.getTiming()], CODE_VARIABLES::OUTCOMES_SEPARATOR_IN_MEDIA_FILE);
    
    srand(time(NULL));
    int randomOutcome = rand()%(outcomes.size());
    std::string outcome = outcomes[randomOutcome]; 
    toLowerCase(outcome);
    
    try{
        if(instance->commentary.find(outcome) == instance->commentary.end())
            throw "commentary is not mentioned for the given outcome in the media files\n\n";
        std::vector<std::string> comments = instance->commentary[outcome];
        srand(time(NULL));
        int randomComment = rand()%(comments.size());
        overSummary = overSummary + "   " + comments[randomComment]+"\n";
        instance->commentaryWriter->appendNextLine("   " + comments[randomComment]+"\n");
    }catch(const char* error){
        std::cout<<error;
        exit(0);
    }

    return outcome;    
}


void Game::startInnings(int teamBattingId, int teamBowlingId, FileReader& obj, int maxOvers, int maxWkts, int maxOversBowlerCanBowl, int maxBallsInOneOver, int target){
    Team& teamBatting = instance->teams[teamBattingId];
    Team& teamBowling = instance->teams[teamBowlingId];

    bool inningsOver = false;
    std::string commentaryLine;
    std::string overSummary;

    // initial bowlers list
    std::vector<int> bowlersIds = instance->teams[teamBowlingId].bowlersIDs;
    int lastBowlerId = -1;

    // initial batters ids
    int strikerId = 0, nonStrikerId = 1;

    for(int over=0; over<maxOvers; over++){
        std::cout<<"\nHit enter to start the over no. "<<over+1;
        std::cin.ignore();

        // decide bowler
        int newBowlerId = getBowlerForNewOver(bowlersIds, lastBowlerId, teamBowlingId, maxOversBowlerCanBowl, maxBallsInOneOver);
    
        for(int ball=1; ball<=maxBallsInOneOver; ball++){
            commentaryLine = "over " + std::to_string(over) + "." + std::to_string(ball) +":-\n";
            instance->commentaryWriter->appendNextLine(commentaryLine);
            overSummary = overSummary + commentaryLine;
            commentaryLine = "   bowler: " + teamBowling.players[newBowlerId].playerName + "\n"; 
            instance->commentaryWriter->appendNextLine(commentaryLine);
            overSummary = overSummary + commentaryLine;
            commentaryLine = "   striker: " + teamBatting.players[strikerId].playerName + "\n"; 
            instance->commentaryWriter->appendNextLine(commentaryLine);
            overSummary = overSummary + commentaryLine;
            commentaryLine = "   nonstriker: " + teamBatting.players[nonStrikerId].playerName + "\n"; 
            instance->commentaryWriter->appendNextLine(commentaryLine);
            overSummary = overSummary + commentaryLine;


            // check if input of this ball is there or not
            if(obj.hasReachedEndOfFile()){
                std::cout<<"error while reading the file...game input is not having complete data\n";
            }
                       

            // get outcome of this ball
            std::string outcomeOnBall = getOutcomeOnBall(obj, teamBattingId, teamBowlingId, strikerId, newBowlerId, overSummary);           


            // update ball bowled by bowler by one and also ball played by batter by one
            teamBowling.players[newBowlerId].updateBallsBowled();
            teamBatting.players[strikerId].updateBallsPlayed();
                       

            // update team runs, team wickets if wicket is taken, batter runs and also runs given away by bowler
            if(outcomeOnBall == CODE_VARIABLES::WKT){
                teamBatting.updateTeamWickets();
                if(teamBatting.getTeamWickets() >= maxWkts){
                    inningsOver = true;
                    break;
                }else{
                    int newBatterId = std::max(strikerId, nonStrikerId) + 1;
                    strikerId = newBatterId;
                }       
            }else{
                try{
                    int runs = std::stoi(outcomeOnBall);  

                    teamBatting.updateTeamRuns(runs);
                    teamBatting.players[strikerId].updateRunsScored(runs);
                    teamBowling.players[newBowlerId].updateRunsGivenAway(runs);
                    
                    if((target!=-1) && (instance->teams[teamBattingId].getTeamruns() >= target)){
                        inningsOver = true;
                        commentaryLine = "   team runs: " + std::to_string(teamBatting.getTeamruns()) + "\n";
                        instance->commentaryWriter->appendNextLine(commentaryLine);
                        overSummary = overSummary + commentaryLine;
                        commentaryLine = "   team wickets: " + std::to_string(teamBatting.getTeamWickets()) + "\n";
                        instance->commentaryWriter->appendNextLine(commentaryLine);
                        overSummary = overSummary + commentaryLine;
                        std::cout<<overSummary;
                        break;
                    }
                    
                    // update strike if runs are odd
                    if(runs%2)
                        std::swap(strikerId, nonStrikerId);    
                }catch(...){
                    std::cout<<"Outcome on this ball is neither wicket nor the valid runs...Its a different string not an integer\n\n";
                    exit(0);
                }
            }
                       
            commentaryLine = "   team runs: " + std::to_string(teamBatting.getTeamruns()) + "\n";
            instance->commentaryWriter->appendNextLine(commentaryLine);
            overSummary = overSummary + commentaryLine;
            commentaryLine = "   team wickets: " + std::to_string(teamBatting.getTeamWickets()) + "\n";
            instance->commentaryWriter->appendNextLine(commentaryLine);
            overSummary = overSummary + commentaryLine;
            std::cout<<overSummary;    
        }

        if(inningsOver){
            break;
        }
                   
        // change strike at the end of over
        std::swap(strikerId, nonStrikerId);

        // update lastBowlerId as well
        lastBowlerId = newBowlerId;
    }
    
    commentaryLine = "\nend of innings: " + teamBatting.teamName + " score - " + std::to_string(teamBatting.getTeamruns()) + "/" + std::to_string(teamBatting.getTeamWickets()) + "\n\n";
    instance->commentaryWriter->appendNextLine(commentaryLine);
    std::cout<<commentaryLine;
}


void Game::updateSummaryOfOneInnings(int teamBattingId, int teamBowlingId){
    Team& battingFirst = instance->teams[teamBattingId];
    Team& bowlingFirst = instance->teams[teamBowlingId];

    std::string summaryLine;
    summaryLine = "\n" + battingFirst.teamName + " batting scorecard:-\n\n";
    instance->summaryWriter->appendNextLine(summaryLine);
    for(auto& player : battingFirst.players){
        summaryLine = player.playerName + " scored " + std::to_string(player.getRunsScored()) + " runs from " + std::to_string(player.getBallsPlayed()) + " balls\n"; 
        instance->summaryWriter->appendNextLine(summaryLine);
    }
    summaryLine = "\n" + bowlingFirst.teamName + " bowling scorecard:-\n\n";
    instance->summaryWriter->appendNextLine(summaryLine);
    for(auto& playerId : bowlingFirst.bowlersIDs){
        Player& p = bowlingFirst.players[playerId];
        summaryLine = p.playerName + " gave away " + std::to_string(p.getRunsGivenAway()) + " runs from " + std::to_string(p.getBallsBowled()) + " balls\n"; 
        instance->summaryWriter->appendNextLine(summaryLine);
    }
    summaryLine = "\n" + battingFirst.teamName + " score- " + std::to_string(battingFirst.getTeamruns()) + "/" + std::to_string(battingFirst.getTeamWickets()) + "\n\n"; 
    instance->summaryWriter->appendNextLine(summaryLine); 
}


void Game::updateSummary(){
    updateSummaryOfOneInnings(teamBattingFirstId, teamBowlingFirstId);
    updateSummaryOfOneInnings(teamBowlingFirstId, teamBattingFirstId);
}


void Game::startGame(){
    // filereader object
    FileReader obj = FileReader(PATH_VARIABLES::GAME_INPUT_FILEPATH);
    std::string commentaryLine;

    Team& battingFirst = instance->teams[teamBattingFirstId];
    Team& bowlingFirst = instance->teams[teamBowlingFirstId];

    // first innings
    commentaryLine = "Let's begin innings one\n\n";
    std::cout<<commentaryLine;
    instance->commentaryWriter->appendNextLine(commentaryLine);
    int target = -1;
    instance->startInnings(teamBattingFirstId, teamBowlingFirstId, obj, CRIC_VARIABLES::MAX_OVERS, CRIC_VARIABLES::MAX_WKTS, CRIC_VARIABLES::MAX_OVERS_BOWLER_CAN_BOWL, CRIC_VARIABLES::MAX_BALLS_IN_ONE_OVER, target);
    
    // second innings
    commentaryLine = "Let's begin innings two\n\n";
    std::cout<<commentaryLine;
    instance->commentaryWriter->appendNextLine(commentaryLine);
    target = battingFirst.getTeamruns() + 1;
    instance->startInnings(teamBowlingFirstId, teamBattingFirstId, obj, CRIC_VARIABLES::MAX_OVERS, CRIC_VARIABLES::MAX_WKTS, CRIC_VARIABLES::MAX_OVERS_BOWLER_CAN_BOWL, CRIC_VARIABLES::MAX_BALLS_IN_ONE_OVER, target);
    
    // update match summary
    instance->updateSummary();
    
    // result
    if(battingFirst.getTeamruns() < bowlingFirst.getTeamruns())
        commentaryLine = bowlingFirst.teamName + " won the match by " + std::to_string(CRIC_VARIABLES::MAX_WKTS - bowlingFirst.getTeamWickets()) + " wickets\n"; 
    else if(battingFirst.getTeamruns() > bowlingFirst.getTeamruns())
        commentaryLine = battingFirst.teamName + " won the match by " + std::to_string(battingFirst.getTeamruns()-bowlingFirst.getTeamruns()) + " runs\n"; 
    else{
        commentaryLine = "match ended with tie\n";
        matchTied = true;
    }
    std::cout<<commentaryLine;
    instance->summaryWriter->appendNextLine(commentaryLine);
    instance->commentaryWriter->appendNextLine(commentaryLine);
}


void Game::startSuperOver(){
    // load input
    inputGenerator(PATH_VARIABLES::GAME_SUPER_OVER_INPUT_FILEPATH, CRIC_VARIABLES::SUPEROVERS, CRIC_VARIABLES::NO_OF_TEAMS, bowlCards, shots, timings);

    FileReader obj = FileReader(PATH_VARIABLES::GAME_SUPER_OVER_INPUT_FILEPATH);
    std::string commentaryLine;
    Team& battingFirst = instance->teams[teamBattingFirstId];
    Team& bowlingFirst = instance->teams[teamBowlingFirstId];
    
    battingFirst.resetTeamRuns();
    battingFirst.resetTeamWickets();
    bowlingFirst.resetTeamRuns();
    bowlingFirst.resetTeamWickets();
    for(auto& playerId : battingFirst.bowlersIDs){
        battingFirst.players[playerId].resetBallsBowled();
    }
    for(auto& playerId : bowlingFirst.bowlersIDs){
        bowlingFirst.players[playerId].resetBallsBowled();
    }

    commentaryLine = "\n\n\nLet's begin super over!!!\n\n\n";
    std::cout<<commentaryLine;
    instance->commentaryWriter->appendNextLine(commentaryLine);

    // first innings
    commentaryLine = "Let's begin innings one\n\n";
    std::cout<<commentaryLine;
    std::cout<<"Hit enter to continue\n\n";
    std::cin.ignore();
    instance->commentaryWriter->appendNextLine(commentaryLine);
    int target = -1;
    instance->startInnings(teamBattingFirstId, teamBowlingFirstId, obj, CRIC_VARIABLES::SUPEROVERS, CRIC_VARIABLES::MAX_WKTS_IN_SUPEROVER, CRIC_VARIABLES::MAX_OVERS_BOWLER_CAN_BOWL_IN_SUPEROVER, CRIC_VARIABLES::MAX_BALLS_IN_ONE_OVER, target);
    
    // second innings
    commentaryLine = "Let's begin innings two\n\n";
    std::cout<<commentaryLine;
    std::cout<<"Hit enter to continue\n\n";
    std::cin.ignore();
    instance->commentaryWriter->appendNextLine(commentaryLine);
    target = battingFirst.getTeamruns() + 1;
    instance->startInnings(teamBowlingFirstId, teamBattingFirstId, obj, CRIC_VARIABLES::SUPEROVERS, CRIC_VARIABLES::MAX_WKTS_IN_SUPEROVER, CRIC_VARIABLES::MAX_OVERS_BOWLER_CAN_BOWL_IN_SUPEROVER, CRIC_VARIABLES::MAX_BALLS_IN_ONE_OVER, target);
    
    // result
    if(battingFirst.getTeamruns() < bowlingFirst.getTeamruns())
        commentaryLine = bowlingFirst.teamName + " won the super over\n";
    else if(battingFirst.getTeamruns() > bowlingFirst.getTeamruns())
        commentaryLine = battingFirst.teamName + " won the super over\n";
    else{
        commentaryLine = "super over ended with tie\n";
        matchTied = true;
    }
    std::cout<<commentaryLine;
    instance->summaryWriter->appendNextLine(commentaryLine);
    instance->commentaryWriter->appendNextLine(commentaryLine);
}


bool Game::isMatchTied(){
    return matchTied;
}


void Game::showSummary(){
    delete summaryWriter;
    std::cout<<"\n\nDo you want to see the match summary? (Press y for yes and n for no)\n\n";
    char ch;
    std::cin>>ch;
    if(ch == 'y'){
        FileReader obj = FileReader(PATH_VARIABLES::MATCH_SUMMARY_FILEPATH);
        while(!obj.hasReachedEndOfFile()){
            std::string line = obj.getNextLine();
            std::cout<<line<<"\n";
        }
    }
}