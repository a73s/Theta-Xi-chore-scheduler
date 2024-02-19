/*
Author: Adam Seals
Date: 1/12/24
*/

#include <string>

#include "sheet.h"
#include "file.h"
#include "func.h"

Sheet::Sheet(const std::string & title, const std::string & date, const std::string & houseFilter){

    this->title = title;
    this->date = date;
    this->houseFilterStr = houseFilter;
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

    oFile.WriteLine("### " + this->title);
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

bool Sheet::Fill(std::vector<Person> * const primaryPool, std::vector<Person> * const secondaryPool){

    std::vector<Person>* activePoolPtr = primaryPool;//this is so we can swap the community pool in when the new house pool runs out
    std::string daysString = "";
    bool canBePledge = false;
    bool canBeEboard = false;
    int dayNum = 0;

    for(int i = 0; i < this->NumDetails(); i++){

        daysString = this->DaysString(i);
        canBePledge = this->NumPeople(i) > 1;

        for(int j = 0; j < static_cast<int>(daysString.size()); j++){

            for(int k = 0; k < this->NumPeople(i); k++){
                
                //only catches the primary pool runout, secondary pool runout is caught by the randomPerson() function returning an error
                //we only catch the primary run out here so that we can quickly swap in the secondary pool
                if(primaryPool->size() < 1 && activePoolPtr == primaryPool){

                    if(secondaryPool == nullptr){

                        std::cout << "Error: " + this->title + " pool has run out of people before the sheet was complete" << std::endl;
                        this->Warn();
                        return 1;
                    }
                    
                    std::cout << this->title + " pool has run out of people before the sheet was complete, attempting to barrow from secondary pool." << std::endl;
                    activePoolPtr = secondaryPool;
                }

                dayNum = getDayNum(daysString[j]);
                canBeEboard = (dayNum != 0) ? true:false;

                if(dayNum != -1){
                    
                    try{

                        Person aPerson = randomPerson(*activePoolPtr, canBeEboard, canBePledge, this->houseFilterStr);
                        this->addPerson(aPerson.Label(), i, dayNum);
                    }
                    catch(char *errStr){//catches the error that there is nobody qualified
                        
                        this->Warn();
                        std::cout << errStr << std::endl;
                        return 1;
                    }
                }
            }
        }
    }
    
    return 0;
}
