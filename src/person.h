/*
Author: Adam Seals
Date: 1/12/24
*/
#pragma once

#include <string>

class Person{

    public:

    Person(const std::string & l, const bool isEboard, const bool isPledge, const bool isGraduating, const bool canBeBarrowed) : label(l), eboard(isEboard), pledge(isPledge), graduating(isGraduating) , canBeBarrowedFromCommunity(canBeBarrowed){};
    Person(const std::string & l) : label(l){};

    bool IsPledge() const {return pledge;}
    bool IsEboard() const {return eboard;}
    bool IsGraduating() const {return graduating;}
    std::string Label() const {return label;}
    bool CanBeBarrowedFromCommunity() const {return canBeBarrowedFromCommunity;}

    //friend inline bool operator == (Person & lhs, Person & rhs) {return lhs.Label() == rhs.Label();}
    bool operator == (const Person & rhs) const {return label == rhs.Label();}
    bool operator != (const Person & rhs) const {return !((*this) == rhs);}

    private:

    std::string label = "";
    bool eboard = 0;
    bool pledge = 0;
    bool graduating = 0;
    bool canBeBarrowedFromCommunity = 0;//this is so that I can check if a person is in the new house when barrowing people from the community pool, not used for anything else

};




