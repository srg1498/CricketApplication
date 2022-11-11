#ifndef GAMEINPUTLINESTRUCTURE_HPP
#define GAMEINPUTLINESTRUCTURE_HPP

#include<iostream>
#include<string>

struct GameInputLineStructure{
    public:
            GameInputLineStructure(std::string bowlCard, std::string shot, std::string timing);
            
            std::string getBowlCard();
            std::string getShot();
            std::string getTiming();

    private:
            std::string bowlCard;
            std::string shot;
            std::string timing;
};


#endif