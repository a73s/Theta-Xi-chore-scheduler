/*
Author: Adam Seals
Date: 1/12/24
Purpose: Automatic detail maker
*/

/*
todo:
an infinite loop can happen while looking for a person if there is only an eboard left and its looking for a monday slot
so we need to return an error if !canBeEboard && the only people left is eboards

make an error state for all sheets(for the eboard thing)

*/

#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <cstdio>

#ifdef _WIN32
    #include <windows.h>
    #include <shellapi.h>
#endif
//#include <iostream>

#include "func.h"
#include "detail.h"
#include "person.h"
#include "sheet.h"

int main(){
    
    srand(time(NULL));

    //lists of details will get read in from files
    std::vector <Detail> communityDetails = {};
    std::vector <Detail> newHouseDetails = {};
    std::vector <Detail> oldHouseDetails = {};

    //all people in their respective houses
    std::vector <Person> newHouse = {};
    std::vector <Person> oldHouse = {};

    //these will be used to keep track of who still owes details
    std::vector <Person> communityPool = {};
    std::vector <Person> newHousePool = {};
    std::vector <Person> oldHousePool = {};

    managePledgeTimer(PLEDGE_TIME_DAYS);
    readInData(communityDetails, newHouseDetails, oldHouseDetails, newHouse, oldHouse);

    //put the people in the pools
    for(int i = 0; i < static_cast<int>(newHouse.size()); i++){

        if(!newHouse[i].IsGraduating()){

            newHousePool.push_back(newHouse[i]);

            if(!newHouse[i].IsEboard()){

                communityPool.push_back(newHouse[i]);
            }
        }
    }

    //same thing for old house
    for(int i = 0; i < static_cast<int>(oldHouse.size()); i++){

        if(!oldHouse[i].IsGraduating()){

            oldHousePool.push_back(oldHouse[i]);

            if(!oldHouse[i].IsEboard()){

                communityPool.push_back(oldHouse[i]);
            }
        }
    }

    std::string date;
    std::cout << "Enter the date to be shown on the detail sheets: ";
    getline(std::cin, date);

    Sheet communitySheet("Community", date);
    Sheet newHouseSheet("New House", date);
    Sheet oldHouseSheet("Old House" , date);

    for(int i = 0; i < static_cast<int>(communityDetails.size()); i++){

        communitySheet.addDetail(communityDetails[i]);
    }

    for(int i = 0; i < static_cast<int>(newHouseDetails.size()); i++){

        newHouseSheet.addDetail(newHouseDetails[i]);
    }

    for(int i = 0; i < static_cast<int>(oldHouseDetails.size()); i++){

        oldHouseSheet.addDetail(oldHouseDetails[i]);
    }

    std::vector<Person>* activePoolPtr = &newHousePool;//this is so we can swap the community pool in when the new house pool runs out
    std::string daysString = "";
    bool canBePledge = false;
    bool canBeEboard = false;
    int dayNum = 0;
    int pledgePriority = 0;//implementing this variable actually maked it less likely for a pledge to be chosen, I just thought it would be funny

    //generating new house sheet. New house sheet is a special case among the sheets, 
    //it often does not have enough people in its main pool to be able to fill it
    //thus there are a few different things between the new house fill and the others
    for(int i = 0; i < newHouseSheet.NumDetails(); i++){

        daysString = newHouseSheet.DaysString(i);
        canBePledge = newHouseSheet.NumPeople(i) > 1;

        for(int j = 0; j < static_cast<int>(daysString.size()); j++){

            for(int k = 0; k < newHouseSheet.NumPeople(i); k++){

                if(newHousePool.size() < 1 && activePoolPtr == &newHousePool){

                    std::cout << "New house pool has run out of people before the sheet was complete, attempting to barrow from community pool." << std::endl;
                    activePoolPtr = &communityPool;
                }

                dayNum = getDayNum(daysString[j]);
                pledgePriority = (k == 0 && canBePledge)? ((i + 1) * PLEDGE_PRIORITY_MULTIPLIER) : (0);
                canBeEboard = (dayNum != 0) ? true:false;

                if(dayNum != -1){

                    Person aPerson = randomPerson((*activePoolPtr), canBeEboard, pledgePriority, true);

                    //this will only happen if there are no newhouse people left in the community pool
                    if(aPerson.Label() == "error"){

                        newHouseSheet.Warn();
                        goto endNewHouseSheet;//break all 3 loops

                    }else{

                        newHouseSheet.addPerson(aPerson.Label(), i, dayNum);
                    }
                }
            }
        }
    }

    endNewHouseSheet:

    std::cout << "Unassigned from new house pool:" << std::endl;

    for(int i = 0; i < static_cast<int>(newHousePool.size()); i++){

        std::cout << newHousePool[i].Label() << std::endl;
    }

    //generating old house sheet
    for(int i = 0; i < oldHouseSheet.NumDetails(); i++){

        daysString = oldHouseSheet.DaysString(i);
        canBePledge = (oldHouseSheet.NumPeople(i) > 1);

        for(int j = 0; j < static_cast<int>(daysString.size()); j++){

            for(int k = 0; k < oldHouseSheet.NumPeople(i); k++){

                if(oldHousePool.size() < 1){

                    std::cout << "Old house pool has run out of people befor the sheet was complete, exiting" << std::endl;
                    oldHouseSheet.Warn();
                    goto endOldHouseSheet;//breaks all 3 loops
                }

                dayNum = getDayNum(daysString[j]);
                pledgePriority = (k == 0 && canBePledge)? ((i + 1) * PLEDGE_PRIORITY_MULTIPLIER) : (0);//in theory there should not be pledges in the old house anyway but i figured i would do this just in case
                canBeEboard = (dayNum != 0) ? true:false;

                if(dayNum != -1){
                    
                    Person aPerson = randomPerson(oldHousePool, canBeEboard, pledgePriority);

                    //this will only happen if there are no newhouse people left in the community pool
                    if(aPerson.Label() == "error"){

                        oldHouseSheet.Warn();
                        goto endOldHouseSheet;//break all 3 loops

                    }else{

                        oldHouseSheet.addPerson(aPerson.Label(), i, dayNum);
                    }
                } 
            }
        }
    }

    endOldHouseSheet:

    std::cout << "Unassigned from old house pool:" << std::endl;

    for(int i = 0; i < static_cast<int>(oldHousePool.size()); i++){

        std::cout << oldHousePool[i].Label() << std::endl;
    }

    //generating community sheet
    for(int i = 0; i < communitySheet.NumDetails(); i++){

        daysString = communitySheet.DaysString(i);
        canBePledge = (communitySheet.NumPeople(i) > 1);

        for(int j = 0; j < static_cast<int>(daysString.size()); j++){

            for(int k = 0; k < communitySheet.NumPeople(i); k++){

                if(communityPool.size() < 1){

                    std::cout << "Community pool has run out of people before the sheet was complete." << std::endl;
                    communitySheet.Warn();
                    goto endCommunitySheet;//breaks all 3 loops
                }

                dayNum = getDayNum(daysString[j]);
                pledgePriority = (k == 0 && canBePledge)? ((i + 1) * PLEDGE_PRIORITY_MULTIPLIER) : (0);
                canBeEboard = (dayNum != 0) ? true:false;

                if(dayNum != -1){

                    Person aPerson = randomPerson(communityPool, canBeEboard, pledgePriority);

                    //this will only happen if there are no newhouse people left in the community pool
                    if(aPerson.Label() == "error"){

                        communitySheet.Warn();
                        goto endCommunitySheet;//break all 3 loops

                    }else{

                        communitySheet.addPerson(aPerson.Label(), i, dayNum);
                    }
                }  
            }
        }
    }

    endCommunitySheet:

    std::cout << "Unassigned from community pool:" << std::endl;

    for(int i = 0; i < static_cast<int>(communityPool.size()); i++){

        std::cout << communityPool[i].Label() << std::endl;
    }

    communitySheet.Output(COMMUNITY_SHEET_OUTPUT);
    oldHouseSheet.Output(OLD_HOUSE_SHEET_OUTPUT);
    newHouseSheet.Output(NEW_HOUSE_SHEET_OUTPUT);

    #ifdef _WIN32
        ShellExecute(NULL,"open",".\\marktext\\MarkText.exe",SHEETS_OUTPUT_PATH,"", SW_SHOWDEFAULT);
    #endif

    #ifdef __linux__
        system(("./marktext/MarkText.exe " SHEETS_OUTPUT_PATH));
    #endif

    std::cout << "Press enter to quit.";
    getchar();

    return 0;
}
