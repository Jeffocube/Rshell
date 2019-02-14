#ifndef COMMAND_H
#define COMMAND_H
#include <vector>
#include <unistd.h>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include "input.h"
using namespace std;

class commandComp : public Input{
    private:
        vector<Input*> comm;
    public:
        commandComp(vector<Input*> comm){
            this->comm = comm;
        }
        bool execute(){
            unsigned numChildren = comm.size();
            for(unsigned i = 0; i < numChildren; i++){
                comm.at(i)->execute();
            }
        }
};
class commandLeaf : public Input{
    private:
        string activity;
        vector<string> args;
    public:
        commandLeaf(string activity, vector<string> args){
            this->activity = activity;
            this->args = args;
        }
        bool execute(){
            
        
        }

};
#endif