/*
Author: Adam Seals
Date: 1/12/24
*/

#include "detail.h"
#include "func.h"
#include <iostream>
#include <string>

Detail::Detail(const std::string & infoString){

    int sectionNum = 0;
    std::string tempLabel = "";
    std::string days = "";

    //parse infoString for the label, days, and number of people
    for(int i = 0; i < static_cast <int> (infoString.length()); i++){

        if(infoString[i] == ':'){

            sectionNum++;
            continue;
        }

        if(sectionNum != 0 && isspace(static_cast <char> (infoString[i]))){

            continue;
        }

        if(sectionNum == 0){

            tempLabel += infoString[i];
        }

        if(sectionNum == 1){//if in section 2 and the character is not space
            days += infoString[i];
        }

        if(sectionNum == 2 && infoString[i] != '\r'){//if in section 3 and the character is not a space, also make sure that the character is not a carriage return

            this->numPeople = static_cast <int> (infoString[i]) - 48;
        }
    }

    for(int i = 0; i < static_cast <int> (days.length()); i++){
        
        if(getDayNum(days[i]) == -1){

            days.erase(i);
        }
    }

    this->daysString = days;
    this->label = tempLabel;
}

void Detail::Print(){

    using namespace std;

    cout << "Label: " << this->label << endl;
    cout << "Days string: " << this->daysString << endl;
    cout << "Number Of People: " << this->numPeople << endl;
}
