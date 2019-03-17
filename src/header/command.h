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
                int p = k;
                if(comm.at(k + 1) == "<" || comm.at(k + 1) == ">" 
                || comm.at(k + 1) == ">>" || comm.at(k + 1) == "|" || ){
                    k++;
                }
                k = comm.at(k)->execute(k);
                if(comm.at(p)->getPass() == true)
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
            vector<string> tempVec;
            tempVec.push_back(activity);
            for(int o = 0; o < args.size(); o++){
                tempVec.push_back(args.at(o));
            }
            args = tempVec;
            int k = args.size();
            pid_t childPid;
            int status;
            char *argIn[k];
            string str1;
            char* str2;
            for(int t = 0; t < k; t++){
                argIn[t] = &args.at(t)[0u];
            }
            argIn[k] = NULL;
        	childPid = fork();
        	if(childPid == 0){
               execvp(argIn[0], argIn);
               perror(argIn[0]);
               exit(errno);
        	}else{
        		wait(&status);
        		if(status == 0){
        		    pass = true;
        		}else{
                pass = false;
            }
        	}
        	return i;
        }
        string getActivity(int i){
            return activity;
        }
};
#endif