#include<iostream>
#include <vector>
#include <string>
#include <fstream>
#include "StudentData.h"
#include <cassert>
#include <cctype>
#include <climits>

MyParser::MyParser() 
{
};

bool MyParser::isQuote(char c)
{
    if(c == '"')
    {
        isQuoteMark = !isQuoteMark;
        return isQuoteMark;
    }
    else
    {
        return isQuoteMark;
    }


};
int MyParser::numOfQuotes(const std::string &command)
{
    int sum = 0;
    for(int i = 0; i < command.size(); i++)
    {
        if(command[i] == '"')
        {
            sum++;
        }
    }
    return sum;
};


std::string MyParser::trim(const std::string &str, char *seperators)
{
    int firstChar = str.find_first_not_of(seperators);
    int lastChar = str.find_last_not_of(seperators);
    int trimmedStr =  lastChar - firstChar + 1;
    return str.substr(firstChar, trimmedStr);
};
bool MyParser::isValidCondition(const std::string &command)
{
    int sum = 0;
    for(int i = 0; i < command.size(); i++)
    {
        if(command[i] == '=' || command[i] == '>' || command[i] == '<' )
        {
            sum++;
        }
    }
    if(sum > 1)
    {
        return false;
    }
    return true;

};

bool MyParser::isCondition(const std::string &command)
{
    for(int i = 0; i < command.size(); i++)
    {
        if(command[i] == '=' || command[i] == '>' || command[i] == '<' )
        {
            return true;
        }
    }
    return false;

};
std::vector<std::string> MyParser::conditionParser(const std::string &command)
{

    std::vector<std::string> parsed_command;
    std::string token = "";
    
    if(!isValidCondition(command))
    {
        return parsed_command;
    }
    for(int i = 0; i < command.size(); i++)
    {

        if(command[i] == '=' || command[i] == '>' || command[i] == '<')
        {
            std::vector<std::string> subVec = parser(trim(token, mSeparators));
            for(int i = 0; i < subVec.size(); i++)
            {
                 parsed_command.push_back(subVec[i]);
            }
            token.clear();
            token += command[i];
            parsed_command.push_back(trim(token, mSeparators));
            token.clear();  
        }

        else
        {
            token += command[i];
        }
    }
    parsed_command.push_back(trim(token, mSeparators));
    return parsed_command;

};

std::vector<std::string> MyParser::parser(const std::string &command)
{
    
    std::vector<std::string> parsed_command;
    std::string trimmedCommand = trim(command, mSeparators);
    std::string token = "";
    if(numOfQuotes(command) > 2)
    {
        return parsed_command;
    }
    if(command.empty() == true)
    {
        return parsed_command;
    }
    
    if(isCondition(command))
    {
        return conditionParser(command);
    }
    
    for(int i = 0; i < trimmedCommand.size(); i++)
    {
        if(isQuote(trimmedCommand[i]))
        {
            token += trimmedCommand[i];
        }
        else
        {
            
            if(trimmedCommand[i] != mSeparators[0] && trimmedCommand[i] != mSeparators[1])
                token += trimmedCommand[i];
            else
            {
                if(token.size() == 0)
                    continue;
                    else
                    {
                        parsed_command.push_back(token);
                        token.clear();
                    }
                }
        }
    }
    parsed_command.push_back(token);
    
    /*for(int i = 0; i < parsed_command.size(); i++)
    {
        std::cout <<  parsed_command[i] << std::endl;
    }
     std::cout <<  parsed_command.size() << std:: endl;
    */

    return parsed_command;
};

std::vector<std::string> MyParser::operator()(const std::string &command)
{
    return parser(command);
};
bool MyParser::isAllSpace(const std::string &command)
{
    
    for(int i = 0; i < command.size(); i++)
    {
        if(isalnum(command[i]))
        {
            return false;
        }
    }
    return true;
};
//MyManager Class
MyManager::MyManager()
{
    HardDiskManager diskManager;
    mData = diskManager.readFile("Data.txt");
};
bool MyManager::intOverflow(const std::string &str)
{
    
    if(std::stoll(str) > UINT_MAX || std::stoll(str) < 0)
        return true;
    else
        return false;
};
bool MyManager::shortOverflow(const std::string &str)
{
    if(std::stoll(str) > USHRT_MAX || std::stoll(str) < 0)
        return true;
    else
        return false;
};
bool MyManager::notDigit(const std::string &str)
{
    for(int i = 0; i < str.size(); i++)
    {
        if(isdigit(str[i]))
        {
            return false;
        }
    }
    return true;
};
bool MyManager::process(const std::vector<std::string> &command)
{
    
    //input validation
    if(command.size() == 0)
    {
        std::cout << "Please Enter Valid a Command:" << std::endl;
        return false;
    }
    //overflow start
    
    if(command[0] == "ADD")
    {

        if(notDigit(command[1]) || notDigit(command[3]))
        {
            std::cout << "Please Enter Valid a Command:" << std::endl;
            return false;
        }
        if(intOverflow(command[1]) || shortOverflow(command[3]))
        {
            std::cout << "Warning, An Overflow Occurred" << std::endl;
            std::cout << "Please Enter Valid a Command:" << std::endl;
            return false;
        }

        if(command.size() != 4)
        {
            std::cout << "Please Enter Valid a Command:" << std::endl;
            return false;
        }
        add(command);
        return false;

    }
    else if(command[0] == "FIND")
    {
        if(command.size() != 4)
        {
            std::cout << "Please Enter Valid a Command:" << std::endl;
            return false;
        }
        find(command);
        return false;


    }
    else if(command[0] == "REMOVE")
    {
        if(command.size() != 4)
        {
            std::cout << "Please Enter Valid a Command:" << std::endl;
            return false;
        }
        remove(command);
        return false;

    }
    else if( (command[0] == "STOP"))        
    {
        if(command.size() != 1)
        {
            std::cout << "Please Enter Valid a Command:" << std::endl;
            return false;
        }
        stop();
        return true;
    }
    else
    {
        std::cout << "Please Enter Valid a Command:" << std::endl;
        return false;

    }
};
void MyManager::add(const std::vector<std::string> &command)
{
    Student s;
    s.mID = std::stoi(command[1]);
    s.mName = command[2];
    s.mAge = std::stoi(command[3]);
    mData.push_back(s);
    
};
void MyManager::find(const std::vector<std::string> &command)
{

    if (command[2] == "=")
    {
        if(command[1] == "id")
        {
            if(notDigit(command[3]))
            {
                std::cout << "Please Enter Valid a Command:" << std::endl;
                return;
            }
            if(intOverflow(command[3]))
            {
                std::cout << "Warning, An Overflow Occurred" << std::endl;
                std::cout << "Please Enter Valid a Command:" << std::endl;
                return;
            }  
            for(int i = 0; i < mData.size(); i++)
            {
                if(mData[i].mID == std::stoi(command[3]))
                {
                    std::cout << mData[i].mID << "  " << mData[i].mName << "  " << mData[i].mAge  << std::endl;
                }
            }
        }
        if(command[1] == "name")
        {
            for(int i = 0; i < mData.size(); i++)
            {
                if(mData[i].mName == command[3])
                {
                    std::cout << mData[i].mID << "  " << mData[i].mName << "  " << mData[i].mAge  << std::endl;
                }
            }
            
        }
        if(command[1] == "age")
        {
            if(notDigit(command[3]))
            {
                std::cout << "Please Enter Valid a Command:" << std::endl;
                return;
            }
            if(shortOverflow(command[3]))
            {
                std::cout << "Warning, An Overflow Occurred" << std::endl;
                std::cout << "Please Enter Valid a Command:" << std::endl;
                return;
            }  
            for(int i = 0; i < mData.size(); i++)
            {
                if(mData[i].mAge == std::stoi(command[3]))
                {
                    std::cout << mData[i].mID << "  " << mData[i].mName << "  " << mData[i].mAge  << std::endl;
                }
            }
            
        }
    }
    else if (command[2] == ">")
    {
        if(command[1] == "id")
        {
            if(notDigit(command[3]))
            {
                std::cout << "Please Enter Valid a Command:" << std::endl;
                return;
            }
            if(intOverflow(command[3]))
            {
                std::cout << "Warning, An Overflow Occurred" << std::endl;
                std::cout << "Please Enter Valid a Command:" << std::endl;
                return;
            }  
            for(int i = 0; i < mData.size(); i++)
            {
                if(mData[i].mID > std::stoi(command[3]))
                {
                    std::cout << mData[i].mID << "  " << mData[i].mName << "  " << mData[i].mAge  << std::endl;
                }
            }

        }
        if(command[1] == "name")
        {
            for(int i = 0; i < mData.size(); i++)
            {
                if(mData[i].mName > command[3])
                {
                    std::cout << mData[i].mID << "  " << mData[i].mName << "  " << mData[i].mAge  << std::endl;
                }
            }
        }
        if(command[1] == "age")
        {
            if(notDigit(command[3]))
            {
                std::cout << "Please Enter Valid a Command:" << std::endl;
                return;
            }
            if(shortOverflow(command[3]))
            {
                std::cout << "Warning, An Overflow Occurred" << std::endl;
                std::cout << "Please Enter Valid a Command:" << std::endl;
                return;
            }  
            for(int i = 0; i < mData.size(); i++)
            {
                if(mData[i].mAge > std::stoi(command[3]))
                {
                    std::cout << mData[i].mID << "  " << mData[i].mName << "  " << mData[i].mAge  << std::endl;
                }
            }
        }
        
    }
    else if (command[2] == "<")
    {
        if(command[1] == "id")
        {
            if(notDigit(command[3]))
            {
                std::cout << "Please Enter Valid a Command:" << std::endl;
                return;
            }
            if(intOverflow(command[3]))
            {
                std::cout << "Warning, An Overflow Occurred" << std::endl;
                std::cout << "Please Enter Valid a Command:" << std::endl;
                return;
            }  
            for(int i = 0; i < mData.size(); i++)
            {
                if(mData[i].mID < std::stoi(command[3]))
                {
                    std::cout << mData[i].mID << "  " << mData[i].mName << "  " << mData[i].mAge  << std::endl;
                }
            }

        }
        if(command[1] == "name")
        {
            for(int i = 0; i < mData.size(); i++)
            {
                if(mData[i].mName > command[3])
                {
                    std::cout << mData[i].mID << "  " << mData[i].mName << "  " << mData[i].mAge  << std::endl;
                }
            }
        }
        if(command[1] == "age")
        {
            if(notDigit(command[3]))
            {
                std::cout << "Please Enter Valid a Command:" << std::endl;
                return;
            }
            if(shortOverflow(command[3]))
            {
                std::cout << "Warning, An Overflow Occurred" << std::endl;
                std::cout << "Please Enter Valid a Command:" << std::endl;
                return;
            }  
            for(int i = 0; i < mData.size(); i++)
            {
                if(mData[i].mAge < std::stoi(command[3]))
                {
                    std::cout << mData[i].mID << "  " << mData[i].mName << "  " << mData[i].mAge  << std::endl;
                }
            }
        }
        
    }
    else
    {
        std::cout << "Please" << std::endl;
    }
};
void MyManager::remove(const std::vector<std::string> &command)
{
    if (command[2] == "=")
    {
        if(command[1] == "id")
        {
            if(notDigit(command[3]))
            {
                std::cout << "Please Enter Valid a Command:" << std::endl;
                return;
            }
            if(intOverflow(command[3]))
            {
                std::cout << "Warning, An Overflow Occurred" << std::endl;
                std::cout << "Please Enter Valid a Command:" << std::endl;
                return;
            }  
            for(int i = 0; i < mData.size(); i++)
            {
                if(mData[i].mID == std::stoi(command[3]))
                {
                    mData.erase(mData.begin() + i);
                    
                }
            }

        }
        if(command[1] == "name")
        {
            for(int i = 0; i < mData.size(); i++)
            {
                if(mData[i].mName == command[3])
                {
                    mData.erase(mData.begin() + i);
                    
                }
            }
            
        }
        if(command[1] == "age")
        {
            if(notDigit(command[3]))
            {
                std::cout << "Please Enter Valid a Command:" << std::endl;
                return;
            }
            if(shortOverflow(command[3]))
            {
                std::cout << "Warning, An Overflow Occurred" << std::endl;
                std::cout << "Please Enter Valid a Command:" << std::endl;
                return;
            }  
            for(int i = 0; i < mData.size(); i++)
            {
                if(mData[i].mAge == std::stoi(command[3]))
                {
                    mData.erase(mData.begin() + i);
                    
                }
            }
            
        }
    }
    else if (command[2] == ">")
    {
        if(command[1] == "id")
        {
            for(int i = 0; i < mData.size(); i++)
            {
                if(notDigit(command[3]))
                {
                    std::cout << "Please Enter Valid a Command:" << std::endl;
                    return;
                }
                if(intOverflow(command[3]))
                {
                    std::cout << "Warning, An Overflow Occurred" << std::endl;
                    std::cout << "Please Enter Valid a Command:" << std::endl;
                    return;
                }  
                if(mData[i].mID > std::stoi(command[3]))
                {
                    mData.erase(mData.begin() + i);
                    
                }
            }

        }
        if(command[1] == "name")
        {
            for(int i = 0; i < mData.size(); i++)
            {
                if(mData[i].mName > command[3])
                {
                    mData.erase(mData.begin() + i);
                    
                }
            }
        }
        if(command[1] == "age")
        {
            if(notDigit(command[3]))
            {
                std::cout << "Please Enter Valid a Command:" << std::endl;
                return;
            }
            if(shortOverflow(command[3]))
            {
                std::cout << "Warning, An Overflow Occurred" << std::endl;
                std::cout << "Please Enter Valid a Command:" << std::endl;
                return;
            }  
            for(int i = 0; i < mData.size(); i++)
            {
                if(mData[i].mAge > std::stoi(command[3]))
                {
                    mData.erase(mData.begin() + i);
                    
                }
            }
        }
        
    }
    else if (command[2] == ">")
    {
        if(command[1] == "id")
        {
            if(notDigit(command[3]))
            {
                std::cout << "Please Enter Valid a Command:" << std::endl;
                return;
            }
            if(intOverflow(command[3]))
            {
                std::cout << "Warning, An Overflow Occurred" << std::endl;
                std::cout << "Please Enter Valid a Command:" << std::endl;
                return;
            }  
            for(int i = 0; i < mData.size(); i++)
            {
                if(mData[i].mID > std::stoi(command[3]))
                {
                    mData.erase(mData.begin() + i);
                    
                }
            }

        }
        if(command[1] == "name")
        {
            for(int i = 0; i < mData.size(); i++)
            {
                if(mData[i].mName > command[3])
                {
                    mData.erase(mData.begin() + i);
                    
                }
            }
        }
        if(command[1] == "age")
        {
            if(notDigit(command[3]))
            {
                std::cout << "Please Enter Valid a Command:" << std::endl;
                return;
            }
            if(shortOverflow(command[3]))
            {
                std::cout << "Warning, An Overflow Occurred" << std::endl;
                std::cout << "Please Enter Valid a Command:" << std::endl;
                return;
            }  
            for(int i = 0; i < mData.size(); i++)
            {
                if(mData[i].mAge > std::stoi(command[3]))
                {
                    mData.erase(mData.begin() + i);
                    
                    
                }
            }
        }
        
    }
    else
    {
        std::cout << "Please Enter Valid a Command:" << std::endl;
    }

};
bool MyManager::stop()
{
    HardDiskManager diskManager;
    diskManager.writeFile("Data.txt", mData);
    return false;
};

HardDiskManager::HardDiskManager()
{
    
};

std::vector<Student> HardDiskManager::readFile(const std::string &fileName)
{
    MyParser parser;
    std::vector<Student> data;
    std::vector<std::string> studentInfo;
    std::string line;
    std::ifstream file(fileName);
    while(getline(file, line))
    {
        studentInfo = parser.parser(line);
        Student s;
        s.mID = stoi(studentInfo[0]);
        s.mName = studentInfo[1];
        s.mAge = stoi(studentInfo[2]);
        data.push_back(s);
    }
    file.close();
    

    return data;


};
void HardDiskManager::writeFile(const std::string &fileName, const std::vector<Student> &data)
{
    std::ofstream newFile("Data.txt");
    for(int i = 0; i < data.size(); i++)
    {
        newFile << std::to_string(data[i].mID) << " " << data[i].mName << " " << std::to_string(data[i].mAge) << std::endl;

    }
    
    newFile.close();
    

};

