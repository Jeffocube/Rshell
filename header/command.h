#ifndef COMMAND_H
#define COMMAND_H
#include <unistd.h>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include "input.h"
using namespace std;

class command : public Input{
    private:
        enum connector; 
        string activity;
        vector<string> args;
        vector<Input*> comm;
    public:
        command(enum conn, string act, vector<string> args, vector<Input*> comm){
            connector = conn;
            activity = act;
            this->args = args;
            this->comm = comm;
        }
        void execute(){
            this->executeHelper();
            unsigned numChildren = comm.size();
            for(unsigned i = 0; i < numChildren; i++){
                comm.at(i)->execute();
            }
        }
};
#endif