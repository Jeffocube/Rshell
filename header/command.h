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
#include <cstring>
using namespace std;

class commandComp : public Input{
    private:
        vector<Input*> comm;
    public:
        commandComp(){
        }
        void setVec(vector<Input*> vec){
            comm = vec;
        }
        int execute(int i){
            int numChildren = comm.size();
            for(int k = 0; k < numChildren; k++){
                k = comm.at(k)->execute(k);
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
        bool pass;
    public:
        bool getPass(){
            return pass;
        }
        commandLeaf(string activity, vector<string> args){
            this->activity = activity;
            this->args = args;
            pass = false;
        }
        int execute(int i){
            // cout << "executed" << endl;
            int k = args.size();
            pid_t childPid;
            int status;
            char *argIn[k];
            string str1;
            char* str2;
            int t = 0;
            for(t = 0; t < k; t++){
                argIn[t] = &args.at(t)[0u];
            }
            argIn[k] = NULL;
        	childPid = fork();
        	if(childPid == 0){
                if(execvp(activity.c_str(), argIn - 1) != 0){
                    exit(1);
                }
        	}else{
        		waitpid(childPid, &status, 0);
        		if(status == 0){
        		    pass = true;
        		}
        	}
        	return i;
        }
};
#endif