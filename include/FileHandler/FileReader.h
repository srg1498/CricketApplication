#ifndef FILEREADER_HPP
#define FILEREADER_HPP

#include<string>
#include<iostream>
#include<fstream>


class FileReader{
    public:
            FileReader(std::string filePath);
            ~FileReader();
            
            std::string getNextLine();
            bool hasReachedEndOfFile();
            bool isFileEmpty();

    private:
           std::ifstream file;
};

#endif