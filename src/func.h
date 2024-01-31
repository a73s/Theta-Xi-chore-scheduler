/*
Author: Adam Seals
Date: 1/12/24
*/
#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "detail.h"
#include "person.h"

#define COMMUNITY_DETAIL_FILE "Details/community.txt"
#define NEW_HOUSE_DETAIL_FILE "Details/new-house.txt"
#define OLD_HOUSE_DETAIL_FILE "Details/old-house.txt"

#define SHEETS_OUTPUT_PATH "Output"
#define COMMUNITY_SHEET_OUTPUT "Output/community.md"
#define NEW_HOUSE_SHEET_OUTPUT "Output/new-house.md"
#define OLD_HOUSE_SHEET_OUTPUT "Output/old-house.md"

#define EBOARDS_FILE "People/eboards.txt"
#define NEW_HOUSE_FILE "People/new-house.txt"
#define OLD_HOUSE_FILE "People/old-house.txt"
#define PLEDGES_FILE "People/pledges.txt"
#define GRADUATING_FILE "People/graduating-seniors.txt"

#define NEW_HOUSE_TITLE "New House"
#define OLD_HOUSE_TITLE "Old House"
#define COMMUNITY_TITLE "Community"

#define PLEDGE_TIME_DAYS 29
#define SECONDS_IN_DAY 86400

#define DEBUG true

//description: generates a random number in the range (inclusive)
//pre:input 2 positive integers, otherwise will set to default, srand is assumed to be pre-seeded in main
//post: returns the random number within the parameters
int genRand(const int min = 0, const int max = 9);

//description: This functions is meant to de-clutter the main function. all it does is read in data from 
//pre:input vectors by reference, the data inputs will be put there
//post:returns nothing, will populate the vectors
void readInData(std::vector <Detail> & communityDetails, std::vector <Detail> & newHouseDetails, std::vector <Detail> & oldHouseDetails, std::vector <Person> & newHouse, std::vector <Person> & oldHouse);

//desc: checks pledge timers
//in: the number of days that the pledges should be in pledge mode
//out: checks pledge timers, gives them a new timer if they have none, 
void managePledgeTimer(const int timeDays = 30);

//desc: picks a random person, preferPledge is the number of random samples the function will make while looking for a pledge. any further samples will allow non-pledges
//if preferPledge is zero you are guaranteed to get a non-pledge
//if you are barrowing from the community pool(mustBeNewHouse = true), then it will return return a person from the new house
//if there is no new-houser in the given list then it will return a person whos label is "error"
Person randomPerson(std::vector<Person> & persons, const bool canBeEboard, const bool canBePledge, const std::string targetHouse = "");


//desc: returns the day number starting at 0 on monday and ending at 6 on sunday
//in: should input capital character in the set {M,T,W,H,F,S,U}
//out: returns the day number starting at 0 on monday and ending at 6 on sunday, if the given character is not in the set of acceptable character it will return -1
int getDayNum(const char dayChar);

//description: checks if the searchvar is an exact match for an element in the given vector
//pre: input a searchvar and vector of the same type
//post: returns true if the searchvar is in the vector, otherwise returns false
template <typename U>
bool isInVector(const std::vector <U> & theVector, const U & searchVar){

    for(int i = 0; i < static_cast<int>(theVector.size()); i++){

        if(searchVar == theVector[i]){
        
            return 1;
        }
    }

    return 0;
}

