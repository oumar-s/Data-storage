#include <iostream>
#include <vector>
#include "StudentData.h"
//compile using g++ -std=c++11 main.cpp StudentData.cpp -o main
int main(){
    
    MyManager  engine;

    MyParser  parser;
    std::string  userInput;
    bool  shouldStop{false};
    try{    
        while(!shouldStop)
        {
            getline(std::cin, userInput);
            while(parser.isAllSpace(userInput))
            {
                std::cout << "Please Enter a Valid Command" << std::endl;
                getline(std::cin, userInput);
            }
            while(userInput.empty()) 
            {
                std::cout << "Please Enter a Valid Command" << std::endl;
                getline(std::cin, userInput);
            }
        
            shouldStop = engine.process(parser(userInput));
        }
    }
    
    catch(...)
    {
        std::cout << "An unexpected Error Has Occurred, Please Restart The Program. Thank You!" << std::endl;
    } 

};
