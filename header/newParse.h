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
#include "connector.h"
#include "command.h"
using namespace std;
    bool newParse(string inp, commandComp* comp){
        vector<Input*> fillThis;
        //beginning of the whole loop for parsing
        for(int i = 0; i < inp.size(); i++){
            //checks if it is not a connector
                cout << inp.at(i) << endl;
            if(inp.at(i) != '|' && inp.at(i) != '&' && inp.at(i) != ';'){
                cout << inp.at(i) << endl;
                string temp;
                while( i < inp.size() && inp.at(i) != ' ' && inp.at(i) != '0'){
                    temp += inp.at(i);
                    i++;
                }i++;
                cout << temp << endl;
                if(temp != "exit"){// if it is not "exit" the algorithm will continue to add on strings to a vector
                    vector<string> tempStrVec;
                    while(i < inp.size() && inp.at(i) != '0' && inp.at(i) != '|' && inp.at(i) != '&' && inp.at(i) != ';'){// this will loop and add to the vector until it encounters a connector or end
                        string temp1;
                        while(i < inp.size() && inp.at(i) != ' '){
                            temp1 += inp.at(i);
                            i++;
                        }i++;
                        tempStrVec.push_back(temp1);
                    }
                    fillThis.push_back(new commandLeaf(temp, tempStrVec));
                }else{
                    fillThis.push_back(new Exit());
                }
            }else if(inp.at(i) == '|' || inp.at(i) == '&'){
                string tempConn;
                cout << "through" << endl;
                if(inp.at(i) == inp.at(i - 1)){
                    tempConn += inp.at(i);
                    tempConn += inp.at(i - 1);
                    fillThis.push_back(new Connector(tempConn, comp));
                    i++;
                }else if(inp.at(i) == ';'){
                    tempConn += inp.at(i);
                    fillThis.push_back(new Connector(tempConn, comp));
                }else{
                    cout << "Failed" << endl;
                    return true;
                }
            }else{
                cout << "Finally" << endl;
            }
        }comp->setVec(fillThis);
        return false;
    }

#endif