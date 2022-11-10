#ifndef TEAMSMEDIAFOLDERLOADER_HPP
#define TEAMSMEDIAFOLDERLOADER_HPP

#include<iostream>
#include<string>
#include<vector>
#include<map>
#include "./MediaFolderLoader.h"

class TeamsMediaFolderLoader : public MediaFolderLoader{
    public:
           TeamsMediaFolderLoader(std::string folderPath);
           ~TeamsMediaFolderLoader();

           void loadResDictionary();
           std::map<std::string, std::map<std::string, std::string>> getResDictionary();

    private:
           std::map<std::string, std::map<std::string, std::string>> teamsInfoDictionary;
};


#endif