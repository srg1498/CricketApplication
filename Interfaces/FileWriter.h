#ifndef FILEWRITER_HPP
#define FILEWRITER_HPP

#include<string>
#include<iostream>
#include<fstream>

class FileWriter{
    public:
            FileWriter(std::string filePath);
            ~FileWriter();
            
            void appendNextLine(std::string line);

    private:
           std::ofstream file;
};

#endif