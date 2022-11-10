#include "../Interfaces/utilityModules.h"
#include "../Interfaces/FileWriter.h"
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<locale>
#include<cctype>


// removes empty spaces from left side 
void ltrim(std::string& word){
    word.erase(word.begin(), std::find_if(word.begin(), word.end(), [](unsigned char ch){
        return !std::isspace(ch);
    }));
}


// removes empty spaces from right side
void rtrim(std::string& word){
    word.erase(std::find_if(word.rbegin(), word.rend(), [](unsigned char ch){
        return !std::isspace(ch);
    }).base(), word.end());
}


// removes empty spaces from both left and right side
void trim(std::string& word){
    ltrim(word);
    rtrim(word);
}


// converts string to lower case
void toLowerCase(std::string& word){
    std::transform(word.begin(), word.end(), word.begin(), ::tolower);
}


// split a string into words on the basis of delimiter
std::vector<std::string> stringSplit(std::string& text, char delimiter){
    std::vector<std::string> words;
    std::string word = "";
    for(auto& ch : text){
        if(ch == delimiter){
            trim(word);
            if(word != "")
                words.push_back(word);
                word = "";
        }else{
            word = word + ch;
        }
    }
    trim(word);
    if(word != "")
        words.push_back(word);
        word = "";
    return words;
}


// it generates inputs on the basis of bowlcards, shots and timings for both the innings
void inputGenerator(std::string fileName, int maxOvers, int noOfTeams, std::vector<std::string> bowlCards, std::vector<std::string> shots, std::vector<std::string> timings){
    FileWriter obj = FileWriter(fileName);
    
    int bowlCardsSize = bowlCards.size();
    int shotsSize = shots.size();
    int timingsSize = timings.size();

    for(int innings=0;innings<noOfTeams;innings++){
        for(int balls=0;balls<maxOvers*6;balls++){
            int randomBall = rand()%bowlCardsSize;
            int randomShot = rand()%shotsSize;
            int randomTiming = rand()%timingsSize;
            std::string input = bowlCards[randomBall] + " " + shots[randomShot] + " " + timings[randomTiming] + "\n";
            obj.appendNextLine(input);
        }
    }
}