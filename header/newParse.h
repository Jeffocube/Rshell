#ifndef NEWPARSE_H
#define NEWPARSE_H
#include <unistd.h>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include "input.h"
#include <sstream>
#include <cstring>
#include "command.h"
using namespace std;
    vector<Input*>newParse(string inp){
        vector<Input*> fillThis;
        //beginning of the whole loop for parsing
        for(int i = 0; i < inp.size(); i++){
            
            //checks if it is not a connector
            if(inp.at(i) != '|' && inp.at(i) != '&' && inp.at(i) != ';'){
                
                
                string temp;
                while(inp.at(i) != ' '){
                    temp += inp.at(i);
                    i++;
                }i++;
                if(temp != "exit"){
                vector<string> tempStrVec;
                while(inp.at(i) != '0' && inp.at(i) != '|' && inp.at(i) != '&' && inp.at(i) != ';'){
                    string temp1;
                    while(inp.at(i) != ' '){
                        temp1 += inp.at(i);
                        i++;
                    }i++;
                    tempStrVec.push_back(temp1);
                }
                    fillThis.push_back(new command);
                }
            }
        }
        return fillThis;
    }

#endif