#ifndef CONNECTOR_H
#define CONNECTOR_H
#include <vector>
#include <unistd.h>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include "command.h"
#include "input.h"
using namespace std;

class Connector : public Input{
    private:
        bool pass = true;
        string activity;
        commandComp* parent;
    public:
        bool execute(int* i){
            if(parent->getInComm(*i - 1) == false && activity == "&&"){
                *i++;
                return true;
            }else if(parent->getInComm(*i - 1) == true && activity == "||"){
                *i++;
                return true;
            }else{
                return true;
            }
        
        }
        bool getPass(){
            return pass;
        }

};


#endif