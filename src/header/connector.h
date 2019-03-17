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
#include <fstream>
#include <sys/stat.h> 
#include <fcntl.h>
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
                return i+1;
                //return lhs execute with outfd 
            }else if(activity == "<"){
                //code for opposite redirect
                
            }else if(activity == "|"){
                //code for pipe
            }else if(activity == ">>"){
                //code for redirect append
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