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
       // int in;
      //  int out;
        int outFdStorage;
        int stdoutStorage;
        int getCommIn(int i){
            return comm.at(i)->in;
        }
        int getCommOut(int i){
            return comm.at(i)->out;
        }
        commandComp(){
            //int in = 0;
            //int out = 1;
        }
        void setVec(vector<Input*> vec){
            comm = vec;
        }
        Input* get(int i){
            return comm.at(i);
        }
        int execute(int i){
            int numChildren = comm.size();
            for(int j = 0; j < numChildren; j++){
                if(comm.at(j)->getActivity(j) == "|" || comm.at(j)->getActivity(j) == ">>" || comm.at(j)->getActivity(j) == ">" ){
                    comm.at(j)->execute(j);
                }
            }
            for(int k = 0; k < numChildren; k++){
                int p = k;
                if(k < (comm.size() - 1)){
                  	if(k < comm.size() && comm.at(k)->getActivity(k) == "|" || comm.at(k + 1)->getActivity(k) == "<"){
                         k++; 
                     }
		        }
          	if (comm.at(k)->getActivity(k) == ">"){
          			close(outFdStorage);
                  //cout << "stdout storage = " << stdoutStorage << endl;
          			dup2(stdoutStorage,1);
          			k++;k++;
          		}	
		        if (k < numChildren)
                k = comm.at(k)->execute(k);
                if(comm.at(p)->getPass() == true)
                    pass = true;
            }
          			dup2(stdoutStorage,1);
            
            return i;
        }
        int execOne(int i){
            comm.at(i)->execute(i);
            return i;
        }
        bool getInComm(int i){// returns the pass of an element in the vector at i
            return comm.at(i)->getPass();
        }
        bool getPass(){//returns the pass of the commandComp;
            return pass;
        }
        int getSize(){//returns the size of the commandComp
            return comm.size();
        }
        bool setPPass(bool b, int i){//sets the pass of an object inside
            comm.at(i)->setPass(b, i);
            return true;
        }
        bool setPass(bool b, int i){//sets its own pass
            pass = b;
            return true;
        }
        string getActivity(int i){//gets activity of an object at i
            return comm.at(i)->getActivity(i);
        }
};
class commandLeaf : public Input{
    private:
        string activity;
        vector<string> args;
        bool pass;
    public:
//        int in;
//        int out;
        bool getPass(){
            return pass;
        }
        commandLeaf(string activity, vector<string> args){
            this->activity = activity;
            this->args = args;
            pass = false;
//            in = 0;
//            out = 1;
        }
        bool setPass(bool b, int i){
            pass = b;
            return true;
        }
      	void setIN(int in1)
      	{
      		in = in1;
      	}
      	void setOUT(int out1)
      	{
      		out = out1;
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
            //cout << "in out = " << in << " " << out << endl;
            
            	    dup2(out,1);
                        dup2(in,0);
            //cout << "in out = " << in << " " << out << endl;
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
