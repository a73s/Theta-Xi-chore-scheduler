/*
Author: Adam Seals
Date: 1/12/24
*/

#include <cstdlib>
#include <vector>
#include <string>
#include <ctime>
//#include <cstdio>

#include "func.h"
#include "person.h"
#include "file.h"

int genRand(const int min, const int max){

    return (rand()%(max-min+1)+min);
}

void readInData(std::vector <Detail> & communityDetails, std::vector <Detail> & newHouseDetails, std::vector <Detail> & oldHouseDetails, std::vector <Person> & newHouse, std::vector <Person> & oldHouse){

    //these are for details
    ReadFile communityDetailFile;
    ReadFile newHouseDetailFile;
    ReadFile oldHouseDetailFile;

    //these files are for reading in names
    ReadFile eboardsFile;
    ReadFile newHouseFile;
    ReadFile oldHouseFile;
    ReadFile pledgesFile;
    ReadFile graduatingFile;

    communityDetailFile.Open(COMMUNITY_DETAIL_FILE);
    newHouseDetailFile.Open(NEW_HOUSE_DETAIL_FILE);
    oldHouseDetailFile.Open(OLD_HOUSE_DETAIL_FILE);

    eboardsFile.Open(EBOARDS_FILE);
    newHouseFile.Open(NEW_HOUSE_FILE);
    oldHouseFile.Open(OLD_HOUSE_FILE);
    pledgesFile.Open(PLEDGES_FILE);
    graduatingFile.Open(GRADUATING_FILE);

    //these are for the purpose of determining if people are pledges/eboards/graduating when putting them into the new/old house lists of people
    //it may be costly to loop through each of these vectors every time we need to create a person but its a cost im willing to accept because
    //this paradigm allows the user to put a name in every file which is applicable to that person, vastly simplifying the process of configuration
    std::vector <Person> eboards;
    std::vector <Person> pledges;
    std::vector <Person> graduating;

    std::string fileLine;

    //skip the first line of each file because there is a descriptor line there
    fileLine = communityDetailFile.readLine();
    fileLine = newHouseDetailFile.readLine();
    fileLine = oldHouseDetailFile.readLine();

    //input the details into the lists
    while(!communityDetailFile.eof()){

        fileLine = communityDetailFile.readLine();
        
        if(fileLine.empty()){
            
            continue;
        }

        communityDetails.push_back(Detail(fileLine));
    }

    while(!newHouseDetailFile.eof()){

        fileLine = newHouseDetailFile.readLine();
        
        if(fileLine.empty()){
            
            continue;
        }
        
        newHouseDetails.push_back(Detail(fileLine));
    }

    while(!oldHouseDetailFile.eof()){

        fileLine = oldHouseDetailFile.readLine();
        
        if(fileLine.empty()){
            
            continue;
        }
        
        oldHouseDetails.push_back(Detail(fileLine));
    }

    //skip first line, it is a title
    fileLine = eboardsFile.readLine();
    fileLine = newHouseFile.readLine();
    fileLine = oldHouseFile.readLine();
    fileLine = pledgesFile.readLine();
    fileLine = graduatingFile.readLine();

    //read in the names into eboard/pledge/grad. This allows us to easily check if they are eboard or pledge or grad when it comes to new/old house lists
    while(!graduatingFile.eof()){

        fileLine = graduatingFile.readLine();

        if(!fileLine.empty()){

            graduating.push_back(Person(fileLine));//since the equality operator for person only checks the name, we can skip setting the other variables
        }
    }

    while(!pledgesFile.eof()){

        fileLine = pledgesFile.readLine();

        std::string inFile = "";

        if(!fileLine.empty()){

            int section = 0;

            //we must exclude anything after the ':' because the pledge timer is there
            for(int i = 0; i < static_cast<int>(fileLine.size()); i++){

                if(fileLine[i] == ':'){

                    section++;
                    continue;
                }
                
                if(section == 0){

                    inFile += fileLine[i];
                }
            }

            pledges.push_back(Person(inFile));
        }
    }

    while(!eboardsFile.eof()){

        fileLine = eboardsFile.readLine();

        if(!fileLine.empty()){

            eboards.push_back(Person(fileLine));
        }
    }

    while(!newHouseFile.eof()){

        fileLine = newHouseFile.readLine();

        if(!fileLine.empty()){

            bool isPledge = isInVector<Person>(pledges, Person(fileLine, false, true, false, true));
            bool isEboard = isInVector<Person>(eboards, Person(fileLine, true, false, false, true));
            bool isGraduating = isInVector<Person>(graduating, Person(fileLine, false, false, true, true));

            newHouse.push_back(Person(fileLine, isEboard, isPledge, isGraduating, true));
        }
    }

    while(!oldHouseFile.eof()){

        fileLine = oldHouseFile.readLine();

        if(!fileLine.empty()){

            bool isPledge = isInVector<Person>(pledges, Person(fileLine, false, true, false, false));
            bool isEboard = isInVector<Person>(eboards, Person(fileLine, true, false, false, false));
            bool isGraduating = isInVector<Person>(graduating, Person(fileLine, false, false, true, false));

            oldHouse.push_back(Person(fileLine, isEboard, isPledge, isGraduating, false));
        }
    }

    //close the files
    communityDetailFile.Close();
    newHouseDetailFile.Close();
    oldHouseDetailFile.Close();
    eboardsFile.Close();
    newHouseFile.Close();
    oldHouseFile.Close(); 

    return;
}

void managePledgeTimer(const int timeDays){

    ReadFile pledgesFile;
    pledgesFile.Open(PLEDGES_FILE);
    std::string fileLine;
    std::vector<std::string> fileLinesBuffer;//vector from which we will recreate the file

    fileLine = pledgesFile.readLine();//skip first line, its not a name
    fileLinesBuffer.push_back(fileLine);

    //parse each line then check if they need a date added or if they need to be removed
    while(!pledgesFile.eof()){

        std::string name = "";
        std::string startTime = "";

        fileLine = pledgesFile.readLine();

        if(fileLine.empty()){
        
            continue;
        }

        fileLinesBuffer.push_back(fileLine);
        int section = 0;

        for(int i = 0; i < static_cast<int>(fileLine.size()); i++){

            if(fileLine[i] == ':'){

                section++;
                continue;
            }
                
            switch(section){

                case 0:{

                    name += fileLine[i];
                    break;
                }
                case 1:{

                    if(fileLine[i] != ' '){
                        startTime += fileLine[i];
                    }
                    break;
                }
            }
        }

        //adding pledge timer, or removing him from file if 
        if(startTime.empty()){

            std::string tempstr = fileLinesBuffer[pledgesFile.LineNum() - 1];
            fileLinesBuffer.pop_back();
            fileLinesBuffer.push_back(tempstr + ':' + std::to_string(time(NULL)));

        }else{

            int pledgeEndTime = stoi(startTime) + (timeDays * SECONDS_IN_DAY);

            if(time(NULL) >= pledgeEndTime){
            
                fileLinesBuffer.pop_back();
            }
        }
    }

    pledgesFile.Close();

    WriteFile pledgesWrite;
    pledgesWrite.Open(PLEDGES_FILE);

    for(int i = 0; i < static_cast<int>(fileLinesBuffer.size()); i++){

        pledgesWrite.WriteLine(fileLinesBuffer[i], '\n');
    }

    pledgesWrite.Close();

    return;
}

Person randomPerson(std::vector<Person> & persons, const bool canBeEboard, int preferPledge, const bool mustBeNewHouse){

    int personIndex = 0;
    Person * personPtr;//using a pointer so that we're not copying the person every time we try to pick a random one, that may happen many times
    int numPledges = 0;
    int numEboards = 0;
    int barrows = 0;
    const bool canBePledge = preferPledge > 0;

    for(int i = 0; i < static_cast<int>(persons.size()); i++){

        if(persons[i].IsPledge()){

            numPledges++;
        }
        if(persons[i].CanBeBarrowedFromCommunity()){

            barrows++;
        }
        if(persons[i].IsEboard()){

            numEboards++;
        }
    }

    //preferPledge *= numPledges;

    if((barrows == 0 && mustBeNewHouse) || (numEboards == static_cast<int>(persons.size()) && !canBeEboard)){

        return Person("error", false, false, false, false);
    }
 
    //this method of picking a random person can be expensive if there are very few people in the pool that meet the requirements
    //however randomness is a priority here so its a cost im willing to allow. Some of the cost is mitigated using the person pointer.
    do{

        personIndex = genRand(0, persons.size() - 1);
        personPtr = &(persons[personIndex]);

        if(preferPledge >= 0){
            
            preferPledge--;
        }

    }while((preferPledge >= 0 && !personPtr->IsPledge() && numPledges > 0) || (!canBePledge && personPtr->IsPledge()) || (mustBeNewHouse && !personPtr->CanBeBarrowedFromCommunity()) || (!canBeEboard && personPtr->IsEboard()));

    Person thePerson = *personPtr;
    persons.erase(persons.begin() + personIndex);
    
    return thePerson;
}

int getDayNum(const char dayChar){

    switch(dayChar){

        case 'M':{
            return 0;
            break;
        }
        case 'T':{
            return 1; 
            break;
        }
        case 'W':{
            return 2;
            break;
        }
        case 'H':{
            return 3;
            break;
        }
        case 'F':{
            return 4; 
            break;
        }
        case 'S':{
            return 5; 
            break;
        }
        case 'U':{
            return 6;   
            break;
        }
        default:{
            return -1;
            break;
        }
    }
}
