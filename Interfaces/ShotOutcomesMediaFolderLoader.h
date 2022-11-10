#ifndef SHOTOUTCOMESMEDIAFOLDERLOADER_HPP
#define SHOTOUTCOMESMEDIAFOLDERLOADER_HPP

#include<iostream>
#include<string>
#include<vector>
#include<map>
#include "./MediaFolderLoader.h"

class ShotOutcomesMediaFolderLoader : public MediaFolderLoader{
    public:
           ShotOutcomesMediaFolderLoader(std::string folderPath);
           ~ShotOutcomesMediaFolderLoader();

           void loadResDictionary();
           std::map<std::string, std::map<std::string, std::map<std::string, std::string>>> getResDictionary();

    private:
           std::map<std::string, std::map<std::string, std::map<std::string, std::string>>> shotOutcomesDictionary;
};


#endif