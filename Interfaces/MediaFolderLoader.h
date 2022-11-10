#ifndef MEDIAFOLDERLOADER_HPP
#define MEDIAFOLDERLOADER_HPP

#include<iostream>
#include<string>
#include<vector>

class MediaFolderLoader{
    public:
            MediaFolderLoader(std::string folderPath);
            ~MediaFolderLoader();

            void listAllFilesOfFolder();

    protected:
            std::string folderPath;
            std::vector<std::string> allFiles;
};

#endif