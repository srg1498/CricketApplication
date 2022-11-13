#include "../../include/MediaFolderLoader/ShotOutcomesMediaFolderLoader.h"
#include "../../include/FileHandler/FileReader.h"
#include "../../include/UtilityFunctions/utilityModules.h"
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<unordered_map>
#include<algorithm>


ShotOutcomesMediaFolderLoader::ShotOutcomesMediaFolderLoader(std::string folderPath) : MediaFolderLoader(folderPath){
    //std::cout<<"Derived Constructor called for somfl\n";
}


ShotOutcomesMediaFolderLoader::~ShotOutcomesMediaFolderLoader(){
    //std::cout<<"Derived Destructor called for somfl\n";
}


void ShotOutcomesMediaFolderLoader::loadResDictionary(){
    //std::cout<<"loading shot outcomes data in dictionary\n";
    for(std::string& file : this->allFiles){
        std::string bowlCardName = stringSplit(file, '.')[0];
        toLowerCase(bowlCardName);
        std::string filePath = folderPath + file;
        FileReader obj = FileReader(filePath);
        std::string line = obj.getNextLine();
        std::vector<std::string> words = stringSplit(line, ',');
        std::vector<std::string> shots(words.begin()+1, words.end());
        std::unordered_map<int, std::string> shotsMapping;
        std::map<std::string, std::map<std::string, std::string>> mp;
        int pos = 0;
        for(auto& shot : shots){
            toLowerCase(shot);
            shotsMapping[pos] = shot;
            pos++;
            std::map<std::string, std::string> outcome;
            mp.insert({shot, outcome});
        }

        while(!obj.hasReachedEndOfFile()){
            std::string line = obj.getNextLine();
            if(line == "")
                break;
            std::vector<std::string> words = stringSplit(line, ',');
            toLowerCase(words[0]);
            std::string timing = words[0];
            std::vector<std::string> outcomes(words.begin()+1, words.end());
            int pos = 0;
            for(auto& outcome : outcomes){
                toLowerCase(outcome);
                mp[shotsMapping[pos]].insert({timing, outcome});
                pos++;
            }
        }
        shotOutcomesDictionary.insert({bowlCardName, mp});
    }
    //std::cout<<"data loaded successfully in dictionary\n";
}


std::map<std::string, std::map<std::string, std::map<std::string, std::string>>> ShotOutcomesMediaFolderLoader::getResDictionary(){
    return shotOutcomesDictionary;
}