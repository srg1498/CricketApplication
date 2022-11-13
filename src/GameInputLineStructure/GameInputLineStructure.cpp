#include "../../include/GameInputStructure/GameInputLineStructure.h"
#include "../../include/UtilityFunctions/utilityModules.h"


GameInputLineStructure::GameInputLineStructure(std::string bowlCard, std::string shot, std::string timing){
    this->bowlCard = bowlCard;
    toLowerCase(this->bowlCard);
    this->shot = shot;
    toLowerCase(this->shot);
    this->timing = timing;
    toLowerCase(this->timing);
}


std::string GameInputLineStructure::getBowlCard(){
    return bowlCard;
}


std::string GameInputLineStructure::getShot(){
    return shot;
}


std::string GameInputLineStructure::getTiming(){
    return timing;
}