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

    this->details.push_back(theDetail);
}

void Sheet::addPerson(const Person & thePerson, const int & detailIndex, const int & dayNum){

    this->details[detailIndex].addPerson(thePerson, dayNum);
    return;
}

void Sheet::Output(const std::string & path){

    WriteFile oFile;
    oFile.Open(path);

    oFile.WriteLine("### " + this->title);
    oFile.WriteLine("| Week of " + this->date + "|**Mon.**|**Tues.**|**Wed.**|**Thurs.**|**Fri.**|**Sat.**|**Sun.**|");
    oFile.WriteLine("|-|-|-|-|-|-|-|-|");

    for(int i = 0; i < this->details.size(); i++){

        std::string oLine = "";

        oLine += '|' + this->details[i].Label();

        for(int j = 0; j < 7; j++){

            oLine += "|";
            oLine += this->details[i].peopleToStr(j);
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

    for(int detail_idx = 0; detail_idx < this->NumDetails(); detail_idx++){

        daysString = this->DaysString(detail_idx);
        canBePledge = this->NumPeopleRequired(detail_idx) > 1;

        for(int day_idx = 0; day_idx < static_cast<int>(daysString.size()); day_idx++){

            for(int i = 0; i < this->NumPeopleRequired(detail_idx); i++){

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

                dayNum = getDayNum(daysString[day_idx]);
                canBeEboard = (dayNum != 0) ? true:false;

                if(dayNum != -1){

                    try{

                        Person aPerson("none");
                        aPerson = randomPerson(*activePoolPtr, canBeEboard, canBePledge, this->houseFilterStr, this->details[detail_idx], day_idx);
                        this->addPerson(aPerson.Label(), detail_idx, dayNum);
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
