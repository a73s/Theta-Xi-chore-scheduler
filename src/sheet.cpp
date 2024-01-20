/*
Author: Adam Seals
Date: 1/12/24
*/

#include <string>

#include "sheet.h"
#include "file.h"

Sheet::Sheet(const std::string & title, const std::string & date){

    this->title += title;
    this->date = date;
}

void Sheet::addDetail(const Detail & theDetail){



    this->labels.push_back(theDetail.Label());
    std::vector <std::string> aStrVec = {"","","","","","",""};
    this->days.push_back(aStrVec);
    this->numDetails++;
    this->numPeople.push_back(theDetail.NumPeople());
    this->daysString.push_back(theDetail.DaysString());

}

void Sheet::addPerson(const std::string & name, const int & detailIndex, const int & dayNum){

    if((this->days[detailIndex])[dayNum].empty()){

        (this->days[detailIndex])[dayNum] = name;
    }else{

        (this->days[detailIndex])[dayNum] += (" & " + name);
    }
    return;
}

void Sheet::Output(const std::string & path){

    WriteFile oFile;
    oFile.Open(path);

    oFile.WriteLine(this->title);
    oFile.WriteLine("| Week of " + this->date + "|**Mon.**|**Tues.**|**Wed.**|**Thurs.**|**Fri.**|**Sat.**|**Sun.**|");
    oFile.WriteLine("|-|-|-|-|-|-|-|-|");

    for(int i = 0; i < this->numDetails; i++){

        std::string oLine = "";

        oLine += '|' + this->labels[i];

        for(int j = 0; j < 7; j++){

            oLine += "|";
            oLine += this->days[i][j];
        }

        oLine += "|";
        oFile.WriteLine(oLine);
    }

    if(this->tooFewWarning){

        oFile.WriteLine("\n> **Warning** \n> Too few people to fill sheet.");
    }

    oFile.Close();
}
