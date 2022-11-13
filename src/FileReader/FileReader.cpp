#include "../../include/FileHandler/FileReader.h"
#include<iostream>
#include<fstream>
#include<string>


// created constructor so that raii concept can be achieved
FileReader::FileReader(std::string filePath){
    try{
        file.open(filePath, std::ios::in);
        if(!file.is_open()){
            throw "error while opening the input file";
        }    
    }catch(const char* error){
        std::cout<<error<<"\n";
        exit(0);
    }
}


// created destructor so that raii concept can be achieved
FileReader::~FileReader(){
    file.close();
}


// returns next line from input file
std::string FileReader::getNextLine(){
    std::string line;
    getline(file, line);
    return line;
}


// returns true/false if file has reached end of file
bool FileReader::hasReachedEndOfFile(){
    return (file.good()) ? false : true;
}


// returns true/false if file is empty or not
bool FileReader::isFileEmpty(){
    while(!hasReachedEndOfFile()){
        std::string line = getNextLine();
        if(line != ""){
            return false;
        }
    }
    return true;
}