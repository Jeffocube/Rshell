#ifndef CONNECTOR_H
#define CONNECTOR_H
#include <fstream>
#include <vector>
#include <unistd.h>
#include <iostream>
#include <string>
#include <sys/types.h>
//#include <ifstream>
#include <sys/wait.h>
#include "command.h"
#include "input.h"
#include <fstream>
#include <sys/stat.h> 
#include <fcntl.h>
using namespace std;

class Connector : public Input{
    private:
        bool pass;
        string activity;
        commandComp* parent;
        int pipeEnds[2];
    public:
        Connector(string activity, commandComp* parent){
            this->activity = activity;
            this->parent = parent;
            pass = false;
        }
        int execute(int i){
            // cout << "Connector executed" << endl;
            // cout << "hello again" << endl;
            if(parent->getInComm(i - 1) == false && activity == "&&"){
                parent->setPPass(true, i + 1);
                return i + 1;
            }else if(parent->getInComm(i - 1) == true && activity == "||"){
                parent->setPPass(true, i + 1);
                return i + 1;
            }else if(parent->getInComm(i - 1) == true && activity == ";"){
                // cout << "SEMICOLON" << endl;
                return i;
            }else if(activity == ">"){
                //code for input redirect
			 
		/*
                string filename = parent->getActivity(i+1);
                int dupout = dup(1);
                int newOut = open(filename.c_str(), O_WRONLY);
                dup2(newOut, 1);
                parent->execOne(i - 1);
                close(newOut);
                dup2(dupout, 1);
                //dup(newOut);
                
                return i+1;
		*/
       //dup2(in, 0);
            		string outf = parent->getActivity(i + 1);
            		int outFd =  open(outf.c_str(),O_WRONLY);
            		parent->outFdStorage = outFd;
            		parent->get(i - 1)->out = outFd;
            		int dupout = dup(1);
			          parent->stdoutStorage = dupout;
            		dup2(outFd, 1);
            	  
		            return i+1;
            }else if(activity == "<"){
                string filename = parent->getActivity(i + 1);
                int dupIn = dup(0);
		parent->stdinStorage = dupIn;
                int newIn = open(filename.c_str(), O_RDONLY);
		parent->inFdStorage = newIn;
		
                if(newIn == -1)
                    return i + 1;
                dup2(newIn, 0);
               // parent->execOne(i - 1);
               // close(newIn);
                //dup2(dupIn, 0);
                //this->setPass(parent->getInComm(i - 1), 1);
               // parent->setPPass(true, i + 1);
                return i + 1;
            }else if(activity == "|"){ 
                //code for pipe
              		
              		pipe(pipeEnds);
                  //cout << "pipeEnds1 = " << pipeEnds[0] << " two = " << pipeEnds[1] << endl;
              		parent->get(i - 1)->out = pipeEnds[1];
              		parent->get(i + 1)->in = pipeEnds[0];
                 //cout << parent->get(i - 1)->out << endl;
                 //cout << parent->get(i + 1)->in << endl;
              
              		return i; 
		         
            }else if(activity == ">>"){
                //code for redirect append
                string filename = parent->getActivity(i+1);
                int dupout = dup(1);
                int newOut = open(filename.c_str(), O_WRONLY | O_APPEND);
		parent->outFdStorage = newOut;
		parent->stdoutStorage = dupout;

                dup2(newOut, 1);
              
                //dup(newOut);
                parent->setPPass(true, i + 1);
                return i+1;
            }else{
                return i;
            }
        }
        bool getPass(){
            return pass;
        }
        bool setPass(bool b, int i){
            pass = b;
            return true;
     	}
        string getActivity(int i){
            return activity;
        }

};


#endif
