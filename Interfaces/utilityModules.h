#ifndef UTILITYMODULES_HPP
#define UTILITYMODULES_HPP

#include<iostream>
#include<vector>
#include<string>

// This header file has all the common modules used in the whole application.

std::vector<std::string> stringSplit(std::string& text, char delimiter);
void toLowerCase(std::string& word);
inline void ltrim(std::string& word);
inline void rtrim(std::string& word);
inline void trim(std::string& word);
void inputGenerator(std::string fileName, int maxOvers, int noOfTeams, std::vector<std::string> bowlCards, std::vector<std::string> shots, std::vector<std::string> timings);

#endif