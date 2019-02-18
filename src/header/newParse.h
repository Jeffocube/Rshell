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
            LABELS:
            if(inp.at(i) == ';'){
                goto LABELSEMI;
            }
            if(i < inp.size() && inp.at(i) == ' '){// to skip spaces
                i++;
            }
            if(inp.at(i) == '#'){
                goto LABEL2;
            }
            if(inp.at(i) == '&' || inp.at(i) == '|' || inp.at(i) == ';'){// this is to add connectors
                LABELSEMI:
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
                    fillThis.push_back(new Connector(tempCon, comp));
                    i += 2;
                }
                if(inp.at(i) == ';'){
                    fillThis.push_back(new Connector(";" , comp));
                    i++;
                }
                start = false;
            }
            if(inp.at(i) != '&' && inp.at(i) != '|' && inp.at(i) != ';' && inp.at(i) != ' ' && inp.at(i) != '#'){// parsing commandLeaf
                start = false;
                string tempAct;
                while( i < inp.size() && inp.at(i) != ' '){// creating activity
                    tempAct += inp.at(i);
                        if(inp.at(i) == '#'){
                            goto LABEL2;
                        }
                        else if(inp.at(i) == ';'){
                            vector<string> empVec;
                            fillThis.push_back(new commandLeaf(tempAct, empVec));
                            goto LABEL2;
                        }
                    i++; 
                    if(i == inp.size()){
                        vector<string> empVec;
                        fillThis.push_back(new commandLeaf(tempAct, empVec));
                        goto LABEL2;
                    }
                    else if(i < (inp.size() - 2) && (inp.at(i + 2) == '|' || inp.at(i + 2) == '&' || inp.at(i + 1) == ';')){
                        vector<string> empVec;
                        tempAct += inp.at(i);
                        i++;
                        if(tempAct.at(tempAct.size() - 1) == ' '){
                            tempAct.pop_back();
                        }
                        fillThis.push_back(new commandLeaf(tempAct, empVec));
                        goto LABELS;
                    }
                }
                if(tempAct != "exit"){// creating exit if activity was not exit
                    string tempArg;
                    vector<string> tempStrVec;
                    while(i < inp.size() && inp.at(i) != '\0' && inp.at(i) != '&' && inp.at(i) != '|' && inp.at(i) != ';'){// parsing the arguments
                        if(inp.at(i) == ' '){
                            i++;
                        }tempArg = "";
                        if(inp.at(i) == '#'){
                            goto LABELNAME;
                        }
                        while( i < inp.size() && inp.at(i) != ' ' && inp.at(i) != '\0' && inp.at(i) != '&' && inp.at(i) != '|' && inp.at(i) != ';' && inp.at(i) != '#'){// goes through each word. Ends if there is a space or NULL
                            tempArg += inp.at(i);
                            i++;
                        }//cout << tempArg << endl;
                        if(tempArg != ""){// if tempArg is empty this means there is nothing to push
                            tempStrVec.push_back(tempArg);
                        }
                    }LABELNAME:
                    if(tempStrVec.size() != 0){// i fthe vector is empty there is nothing to push
                    // cout << "Made a Command" << endl;
                        fillThis.push_back(new commandLeaf(tempAct, tempStrVec));
                    }
                }else{// creating exit
                    fillThis.push_back(new ExitObj());
                }
            }
        }LABEL2:
        comp->setVec(fillThis);
        return false;
    }

#endif