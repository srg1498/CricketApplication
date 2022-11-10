#ifndef COMMENTARYMEDIAFOLDERLOADER_HPP
#define COMMENTARYMEDIAFOLDERLOADER_HPP

#include<iostream>
#include<string>
#include<vector>
#include<map>
#include "./MediaFolderLoader.h"

class CommentaryMediaFolderLoader : public MediaFolderLoader{
    public:
           CommentaryMediaFolderLoader(std::string folderPath);
           ~CommentaryMediaFolderLoader();

           void loadResDictionary();
           std::map<std::string, std::vector<std::string>> getResDictionary();

    private:
           std::map<std::string, std::vector<std::string>> commentaryDictionary;
};


#endif