#include "../Interfaces/MediaFolderLoader.h"
#include<iostream>
#include<string>
#include<dirent.h>
#include<sys\stat.h>
#include<vector>
#include<map>


MediaFolderLoader::MediaFolderLoader(std::string folderPath){
    //std::cout<<"Base Constructor called for media\n";
    this->folderPath = folderPath;
    this->listAllFilesOfFolder();
}


MediaFolderLoader::~MediaFolderLoader(){
    //std::cout<<"Base Destructer called for media\n";
}


void MediaFolderLoader::listAllFilesOfFolder(){
    dirent* d;
    struct stat dst;
    DIR* dr;
    std::string pathReq = this->folderPath;
    dr = opendir(pathReq.c_str());
    if(dr!=NULL){
        for(d=readdir(dr);d!=NULL;d=readdir(dr)){
            std::string type = pathReq + d->d_name;
            if(stat(type.c_str(), &dst) == 0){
                if(dst.st_mode & S_IFREG){
                    this->allFiles.push_back(d->d_name);    
                }
            }
        }
        closedir(dr);
    }
}