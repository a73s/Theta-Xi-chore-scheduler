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
    Sheet(const std::string & title, const std::string & date);

    //desc:adds a detail to the sheet
    //pre:takes a detail
    //post:adds that detail to the sheet, initializing all of its variables
    void addDetail(const Detail & theDetail);

    //desc: adds a person to a particular day on a particular detail
    //pre: input the index of the detail, the name of the person, and the day number (0-6)
    //post: adds the person's name to the specified detail
    void addPerson(const std::string & name, const int & detailIndex, const int & dayNum);

    //desc: outputs the sheet in markdown format to the file path specified
    //pre: input file path
    //post: outputs the sheet in markdown format to the file path specified
    void Output(const std::string & path);

    int NumDetails() const {return numDetails;}
    std::string DaysString(const int index) const {return daysString[index];}
    int NumPeople(const int index) const {return numPeople[index];}
    void Warn() {tooFewWarning = true;}

    private:

    std::string title = "### ";
    std::string date = "";

    int numDetails = 0;
    bool tooFewWarning = false;
    std::vector <std::string> labels = {};//labels for each detail
    std::vector <std::vector<std::string>> days = {};//each detail has a string list of 7 days
    std::vector <int> numPeople = {};//number of people on the detail
    std::vector <std::string> daysString = {};
};