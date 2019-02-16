#ifndef COMMAND_H
#define COMMAND_H
#include <vector>
#include <unistd.h>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "input.h"
using namespace std;

class commandComp : public Input{
    private:
        vector<Input*> comm;
    public:
        commandComp(vector<Input*> comm){
            this->comm = comm;
        }
        bool execute(int* i){
            int numChildren = comm.size();
            for(int k = 0; k < numChildren; k++){
                cout << k << endl;
                cout << "EXECUTING" << endl;
                comm.at(k)->execute(&k);
            }
        }
        bool getInComm(int i){
            return comm.at(i)->getPass();
        }
        bool getPass(){
            return true;
        }
};
class commandLeaf : public Input{
    private:
        string activity;
        vector<string> args;
        bool pass = true;
    public:
        bool getPass(){
            return pass;
        }
        commandLeaf(string activity, vector<string> args){
            this->activity = activity;
            this->args = args;
        }
        bool execute(int* i){
            cout << "Hello3" << endl;
        
        }

};
#endif