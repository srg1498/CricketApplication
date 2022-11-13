#include "../../include/MediaFolderLoader/TeamsMediaFolderLoader.h"
#include "../../include/FileHandler/FileReader.h"
#include "../../include/UtilityFunctions/utilityModules.h"
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<unordered_map>
#include<algorithm>


TeamsMediaFolderLoader::TeamsMediaFolderLoader(std::string folderPath) : MediaFolderLoader(folderPath){
    //std::cout<<"Derived Constructor called for tmfl\n";
}


TeamsMediaFolderLoader::~TeamsMediaFolderLoader(){
    //std::cout<<"Derived Destructor called for tmfl\n";
}


void TeamsMediaFolderLoader::loadResDictionary(){
    //std::cout<<"loading teams data in dictionary\n";
    for(std::string& file : this->allFiles){
        std::string teamName = stringSplit(file, '.')[0];
        toLowerCase(teamName);
        std::string filePath = folderPath + file;
        FileReader obj = FileReader(filePath);
        std::string line = obj.getNextLine();
        std::map<std::string, std::string> mp;

        while(!obj.hasReachedEndOfFile()){
            std::string line = obj.getNextLine();
            if(line == "")
                break;
            std::vector<std::string> words = stringSplit(line, ',');
            std::string playerName = words[0];
            toLowerCase(playerName);
            std::string canBowl = words[1];
            toLowerCase(canBowl);
            mp.insert({playerName, canBowl});
        }
        teamsInfoDictionary.insert({teamName, mp});
    }
    //std::cout<<"data loaded successfully in dictionary\n";
}


std::map<std::string, std::map<std::string, std::string>> TeamsMediaFolderLoader::getResDictionary(){
    return teamsInfoDictionary;
}