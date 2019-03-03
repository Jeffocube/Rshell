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
        bool pass = false;
    public:
        commandComp(){
        }
        void setVec(vector<Input*> vec){
            comm = vec;
        }
        int execute(int i){
            //cout << comm.size() << " <- this is the size" << endl;
            int numChildren = comm.size();
            for(int k = 0; k < numChildren; k++){
                k = comm.at(k)->execute(k);
                if(comm.at(k)->getPass() == true)
                    pass = true;
            }
            return i;
        }
        bool getInComm(int i){
            return comm.at(i)->getPass();
        }
        bool getPass(){
            return pass;
        }
        int getSize(){
            return comm.size();
        }
        bool setPPass(bool b, int i){
            comm.at(i)->setPass(b, i);
            return true;
        }
        bool setPass(bool b, int i){
            pass = b;
        }
        string getActivity(int i){
            return comm.at(i)->getActivity(i);
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
        bool setPass(bool b, int i){
            pass = b;
            return true;
        }
        int execute(int i){
            //cout << "executed" << endl;
            //cout << activity << "<- did this" << endl;
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
                int sh = execvp(activity.c_str(), argIn - 1);
                if(sh == -1){
                    perror(activity.c_str());
                    exit(EXIT_FAILURE);
                }
                    exit(0);
                
                
        	}else{
        		wait(&status);
        		if(status == 0){
        		    pass = true;
        		}
        	}
        	return i;
        }
        string getActivity(int i){
            return activity;
        }
};
#endif