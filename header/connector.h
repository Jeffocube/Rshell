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
        bool pass;
        string activity;
        commandComp* parent;
    public:
        Connector(string activity, commandComp* parent){
            this->activity = activity;
            this->parent = parent;
            pass = false;
        }
        int execute(int i){
            // cout << "hello again" << endl;
            if(parent->getInComm(i - 1) == false && activity == "&&"){
                return i + 1;
            }else if(parent->getInComm(i - 1) == true && activity == "||"){
                return i + 1;
            }else{
                return i;
            }
        }
        bool getPass(){
            return pass;
        }

};


#endif