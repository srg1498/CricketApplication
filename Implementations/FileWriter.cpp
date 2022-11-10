#include "../Interfaces/FileWriter.h"
#include<iostream>
#include<fstream>
#include<string>


// created constructor so that raii concept can be achieved
FileWriter::FileWriter(std::string filePath){
    file.open(filePath, std::ios::out | std::ios::trunc);
}


// created destructor so that raii concept can be achieved
FileWriter::~FileWriter(){
    file.close();
}


// appends new line into output file
void FileWriter::appendNextLine(std::string line){
    file<<line;
}