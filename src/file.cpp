/*
Author: Adam Seals
Date: 1/12/24
*/

#include <string>
#include <iostream>

#include "file.h"

//ReadFile

bool ReadFile::Open(const std::string & path){

    int errorCount = 0;
    this->filePath = path;

    do{

        if(errorCount > 5){

            std::cout << "Exiting due to file openning errors" << std::endl;
            exit(1);
        }

        theFile.open(path.c_str());

        if(!theFile.is_open()){

            std::cout << "Openning of " + path + " failed. Trying again" << std::endl;
            errorCount++;
        }

    }while(!theFile.is_open());

    return 0;
}

bool ReadFile::Close(){

    if(theFile.is_open()){

        theFile.close();
        return 0;
    }

    return 1;
}

std::string ReadFile::readLine(){

    std::string returnVar;

    getline(theFile, returnVar);

    //check for carriage return in the line, need to be removed to avoid issues
    for(int i = 0; i < static_cast<int>(returnVar.size()); i++){

        if(returnVar[i] == '\r')
        returnVar.erase(i);
    } 

    this->lineNum++;

    return returnVar;
}

//WriteFile

bool WriteFile::Open(const std::string & path){

    int errorCount = 0;
    this->filePath = path;

    do{

        if(errorCount > 5){

            std::cout << "Exiting program due to file openning errors" << std::endl;
            exit(1);
        }

        theFile.open(path.c_str());

        if(!theFile.is_open()){

            std::cout << "Openning of " + path + " failed. Trying again" << std::endl;
            errorCount++;
        }

    }while(!theFile.is_open());

    return 0;
}

bool WriteFile::Close(){

    if(theFile.is_open()){
        
        theFile.close();
        return 0;
    }

    return 1;
}

void WriteFile::WriteLine(const std::string & astr, const char endChar){
        
    if(endChar == '\0'){

        theFile << astr;
    }else{

    theFile << (astr + endChar);
    }
}