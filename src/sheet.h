/*
Author: Adam Seals
Date: 1/12/24
*/

#pragma once

#include <string>
#include <vector>

#include "detail.h"
#include "person.h"

class Sheet{

    public:

    //desc:constructor, sets the date and the title
    //pre:input the date in whatever format you want
    //post:edits the title, and firstLine
    Sheet(const std::string & title, const std::string & date, const std::string & houseFilter);

    //desc:adds a detail to the sheet
    //pre:takes a detail
    //post:adds that detail to the sheet, initializing all of its variables
    void addDetail(const Detail & theDetail);

    //desc: adds a person to a particular day on a particular detail
    //pre: input the index of the detail, the person, and the day number (0-6)
    //post: adds the person's name to the specified detail
    void addPerson(const Person & thePerson, const int & detailIndex, const int & dayNum);

    //desc: outputs the sheet in markdown format to the file path specified
    //pre: input file path
    //post: outputs the sheet in markdown format to the file path specified
    void Output(const std::string & path);

    //desc: fills the given sheet
    //pre: input the pointers to primary and secondary sheets, this is so that the second one can be optional
    //post: will fill the sheet using the primary pool and optionally the secondary pool
    bool Fill(std::vector<Person> * const primaryPool, std::vector<Person> * const secondaryPool = nullptr);

    int NumDetails() const {return details.size();}
    std::string DaysString(const int index) const {return details[index].DaysString();}
    int NumPeopleRequired(const int index) const {return details[index].NumPeople();}
    void Warn() {tooFewWarning = true;}

    private:

    std::string title = "";
    std::string date = "";
    std::string houseFilterStr = "";

    bool tooFewWarning = false;
    std::vector <Detail> details = {};
};
