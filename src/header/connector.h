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
        int in;
        int out;
    public:
        Connector(string activity, commandComp* parent){
            this->activity = activity;
            this->parent = parent;
            pass = false;
            in = 0;
            out = 1;
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
                string filename = parent->getActivity(i+1);
                int dupout = dup(1);
                int newOut = open(filename.c_str(), O_WRONLY);
                if(newOut == -1){
                    std::ofstream ofs (filename, std::ofstream::out);
                    newOut = open(filename.c_str(), O_WRONLY);
                }
                dup2(newOut, 1);
                parent->execOne(i - 1);
                close(newOut);
                dup2(dupout, 1);
                return i+1;
                //return lhs execute with outfd 
            }else if(activity == "<"){
                //code for opposite redirect
                string filename = parent->getActivity(i + 1);
                int dupIn = dup(0);
                int newIn = open(filename.c_str(), O_RDONLY);
                dup2(newIn, 0);
                parent->execOne(i - 1);
                close(newIn);
                dup2(dupIn, 0);
                this->setPass(parent->getInComm(i - 1), 1);
                parent->setPPass(true, i + 1);
                return i + 1;
            }else if(activity == "|"){ 
                //code for pipe
                int fds[2];
		
		pipe(fds);
		parent->get(i - 1)->out = fds[1];
		parent->get(i + 1)->in = fds[0];
	        	
	        
		

		//think this works?
		
		
            }else if(activity == ">>"){
                //code for redirect append
                string filename = parent->getActivity(i+1);
                int dupout = dup(1);
                int newOut = open(filename.c_str(), O_WRONLY | O_APPEND);
                if(newOut == -1){
                    std::ofstream ofs (filename, std::ofstream::out);
                    newOut = open(filename.c_str(), O_WRONLY | O_APPEND);
                }
                dup2(newOut, 1);
                parent->execOne(i - 1);
                close(newOut);
                dup2(dupout, 1);
                this->setPass(parent->execOne(i - 1), 1);
                parent->setPPass(true, i + 1);
                //dup(newOut);
                
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
