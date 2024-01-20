/*
Author: Adam Seals
Date: 1/12/24
*/
#pragma once

#include <fstream>

//a simpler interface for reading from files, standardizes the process
class ReadFile{

    public:

    //pre: input the file path to be openned
    //post: if openning the file fails 5 times in a row it exits the program with an error
    //desc: opens a file
    bool Open(const std::string & path);

    //pre: none
    //post: closes the file
    //desc: closes the file
    bool Close();

    //pre: n/a
    //post: returns the next full line in the file, eleminates carriage returns and empty lines
    //desc: reads a file line
    std::string readLine();

    bool eof(){return theFile.eof();}
    int LineNum(){return this->lineNum;}

    private:

    std::ifstream theFile;
    std::string filePath;
    int lineNum = 0;

    
};

//a simpler interface for writing to files, standardizes the process
class WriteFile{

    public:

    //pre: input the file path to be openned
    //post: if openning the file fails 5 times in a row it exits the program with an error
    //desc: opens a file
    bool Open(const std::string & path);

    //pre: none
    //post: closes the file
    //desc: closes the file
    bool Close();

    //pre: a string and an endchar a null character or no input for the end char will result in no endchar
    //post: returns nothing, writes the string and the endchar to the file
    //desc: writes a full line to the file
    void WriteLine(const std::string & astr, const char endChar = '\n');

    private:

    std::ofstream theFile;
    std::string filePath;

    
};


