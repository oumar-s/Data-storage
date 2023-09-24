#pragma once
#include <vector>
#include <iostream>

//todo:
// add in namespaces/const/references as required


//student class
struct Student
{
    unsigned int mID;
    std::string mName;
    unsigned short mAge;
};

//parser class
class MyParser
{
public:
    MyParser();
    std::vector<std::string> parser(const std::string &command);
    std::vector<std::string> operator()(const std::string &command);
    std::vector<std::string> conditionParser(const std::string &command);
    bool isCondition(const std::string &command);
    bool isAllSpace(const std::string &command);
    bool isValidCondition(const std::string &command);
    int numOfQuotes(const std::string &command);
    std::string trim(const std::string &str, char *seperators);
    bool isQuote(char c);


private:
    char mSeparators[2] = {' ', '\t'};
    bool isQuoteMark = false;
};

//disk manager class
class HardDiskManager
{
public:
    HardDiskManager();
    std::vector<Student> readFile(const std::string &fileName);
    void writeFile(const std::string &fileName, const std::vector<Student> &data);
};

//manager class
class MyManager
{
public:
    MyManager();
    bool notDigit(const std::string &str);
    bool intOverflow(const std::string &str);
    bool shortOverflow(const std::string &str);
    bool process(const std::vector<std::string> &command); 
    void add(const std::vector<std::string> &command);
    void find(const std::vector<std::string> &command);
    void remove(const std::vector<std::string> &command);
    bool stop();
    
private:
    std::vector<Student> mData;
};



