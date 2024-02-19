/*
Author: Adam Seals
Date: 1/12/24
Purpose: Automatic detail maker
*/

#include <stdlib.h>
#include <ctime>
#include <string>
#include <vector>
#include <cstdio>


#ifdef _WIN32
    #include <windows.h>
    #include <shellapi.h>
#endif

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

    Sheet communitySheet(COMMUNITY_TITLE, date, "");
    Sheet newHouseSheet(NEW_HOUSE_TITLE, date, NEW_HOUSE_TITLE);
    Sheet oldHouseSheet(OLD_HOUSE_TITLE , date, OLD_HOUSE_TITLE);

    for(int i = 0; i < static_cast<int>(communityDetails.size()); i++){

        communitySheet.addDetail(communityDetails[i]);
    }

    for(int i = 0; i < static_cast<int>(newHouseDetails.size()); i++){

        newHouseSheet.addDetail(newHouseDetails[i]);
    }

    for(int i = 0; i < static_cast<int>(oldHouseDetails.size()); i++){

        oldHouseSheet.addDetail(oldHouseDetails[i]);
    }

    newHouseSheet.Fill(&newHousePool, &communityPool);
    oldHouseSheet.Fill(&oldHousePool, &communityPool);
    communitySheet.Fill(&communityPool);

    std::cout << "Unassigned from new house pool:" << std::endl;

    for(int i = 0; i < static_cast<int>(newHousePool.size()); i++){

        std::cout << newHousePool[i].Label() << std::endl;
    }

    std::cout << "Unassigned from old house pool:" << std::endl;

    for(int i = 0; i < static_cast<int>(oldHousePool.size()); i++){

        std::cout << oldHousePool[i].Label() << std::endl;
    }

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

    #ifdef __linux__//using shellexecute was meant to prevent windows defender complaints but it seems that it is still complaining unless I comment this out
        system(("./marktext/MarkText.exe " SHEETS_OUTPUT_PATH));
    #endif

    std::cout << "Press enter to quit.";
    getchar();

    return 0;
}
