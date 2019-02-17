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
#include "exit.h"
using namespace std;
    bool newParse(string inp, commandComp* comp){
        int i = 0;
        bool start = true;
        vector<Input*> fillThis;
        while(i < inp.size()){
            if(i < inp.size() && inp.at(i) == ' '){// to skip spaces
                i++;
            }
            if(inp.at(i) == '&' || inp.at(i) == '|' || inp.at(i) == ';'){// this is to add connectors
                if(i == 0 || start == true){
                    return true;
                }
                if(comp->getSize() == 0 && i > inp.size() - 3){
                    return true;
                }
                if(inp.at(i + 1) == inp.at(i)){
                    string tempCon;
                    tempCon += inp.at(i);
                    tempCon += inp.at(i + 1);
                    // cout << "Made a connector" << endl;
                    // cout << tempCon << "<- this" << endl;
                    fillThis.push_back(new Connector(tempCon, comp));
                    i += 2;
                }
                if(inp.at(i) == ';'){
                    fillThis.push_back(new Connector(";" , comp));
                    i++;
                }
                start = false;
            }
            if(inp.at(i) != '&' && inp.at(i) != '|' && inp.at(i) != ';' && inp.at(i) != ' '){// parsing commandLeaf
                start = false;
                string tempAct;
                while( i < inp.size() && inp.at(i) != ' '){// creating activity
                    tempAct += inp.at(i);
                    i++; 
                }
                if(tempAct != "exit"){// creating exit if activity was not exit
                    string tempArg;
                    vector<string> tempStrVec;
                    while(i < inp.size() && inp.at(i) != '\0' && inp.at(i) != '&' && inp.at(i) != '|' && inp.at(i) != ';'){// parsing the arguments
                        if(inp.at(i) == ' '){
                            i++;
                        }tempArg = "";
                        while( i < inp.size() && inp.at(i) != ' ' && inp.at(i) != '\0' && inp.at(i) != '&' && inp.at(i) != '|' && inp.at(i) != ';'){// goes through each word. Ends if there is a space or NULL
                            tempArg += inp.at(i);
                            i++;
                        }//cout << tempArg << endl;
                        if(tempArg != ""){// if tempArg is empty this means there is nothing to push
                            tempStrVec.push_back(tempArg);
                        }
                    }
                    if(tempStrVec.size() != 0){// i fthe vector is empty there is nothing to push
                    // cout << "Made a Command" << endl;
                        fillThis.push_back(new commandLeaf(tempAct, tempStrVec));
                    }
                }else{// creating exit
                    fillThis.push_back(new ExitObj());
                }
                
            }
            
            
        }
        comp->setVec(fillThis);
        return false;
    }

#endif