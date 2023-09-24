# How to run the program
Program requires C++ compiler
Example compilation: 
`g++ -std=c++11 main.cpp StudentData.cpp -o program`
`./program Data.txt`
Make sure to provide an input txt file where data will be stored.

# Program Description
The program runs in terminal window and knows the following commands:

## ADD  student_ID  name  age
Adds a student record with corresponding fields. The order of parameters is fixed. Parameters supplied in different order cause error. For example:
ADD 67412  Smith,John  21
ADD   8723333 "Ann Smith"   33
 
## FIND  condition
Prints all records satisfying the condition. See below the example of command and potential output:
FIND  age = 21
67412           Smith,John            21
761              Mary Doe             21
33221212    Jack-Mark            21

FIND  id>1000000
33221212    Jack-Mark            21

           FIND  name = Jack-Mark
           33221212    Jack-Mark            21
           FIND  name = "Ann Smith"
           8723333     Ann Smith            33
           229             Ann Smith            19

## REMOVE  condition
For example:
REMOVE   id< 50000    

## STOP
Exits the application.