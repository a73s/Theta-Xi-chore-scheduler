/*
Author: Adam Seals
Date: 1/12/24
*/

#include <string>
#include <vector>
#include "person.h"

#ifndef DETAIL_H
#define DETAIL_H

class Detail{

    public:

    //pre:infostring should be in the format "<label>:<days(MTWHFSU)>:<number of people>"  the number of people should be a single digit
    //post:sets up the class, assigns a value to the label, numPeopleRequired, and day values
    Detail(const std::string & infoString);

    void Print();
    std::string Label() const {return label;}
    int NumPeople() const {return numPeopleRequired;}
    std::string DaysString() const {return daysString;}
    void addPerson(const Person & thePerson, const int day_idx);
    bool personAlreadyAdded(const Person & thePerson, const int day_idx) const;
    std::string peopleToStr(const int day_idx) const;

    private:

    std::string label;
    std::string daysString;
    std::vector<std::vector<Person>> days_slots;
    int numPeopleRequired;

    void ParseDays(const std::string & days);

};


#endif
