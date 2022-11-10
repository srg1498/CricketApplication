#include "../Interfaces/CommentaryMediaFolderLoader.h"
#include "../Interfaces/FileReader.h"
#include "../Interfaces/utilityModules.h"
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<unordered_map>
#include<algorithm>


CommentaryMediaFolderLoader::CommentaryMediaFolderLoader(std::string folderPath) : MediaFolderLoader(folderPath){
    //std::cout<<"Derived Constructor called for cmfl\n";
}


CommentaryMediaFolderLoader::~CommentaryMediaFolderLoader(){
    //std::cout<<"Derived Destructor called for cmfl\n";
}


// it loads commentary media folder into commentary dictionary  
void CommentaryMediaFolderLoader::loadResDictionary(){
    //std::cout<<"loading commentary in dictionary\n";
    for(std::string& file : this->allFiles){
        std::string outcome = stringSplit(file, '.')[0];
        toLowerCase(outcome);
        std::string filePath = folderPath + file;
        FileReader obj = FileReader(filePath);
        std::vector<std::string> comments;
        
        while(!obj.hasReachedEndOfFile()){
            std::string comment = obj.getNextLine();
            if(comment == "")
                break;
            comments.push_back(comment);
        }
        commentaryDictionary.insert({outcome, comments});
    }
    //std::cout<<"data loaded successfully in dictionary\n";
}


std::map<std::string, std::vector<std::string>> CommentaryMediaFolderLoader::getResDictionary(){
    return commentaryDictionary;
}