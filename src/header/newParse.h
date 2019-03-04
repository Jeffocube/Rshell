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
#include "tester.h"
using namespace std;
Test* makeTest_1(int* i, string str){
    //cout << str << endl;
    int k = 0;
    string tempTestAct = "";
    string tempTestArg = "";
    while(k < str.size() && str.at(k) != ' '){
        tempTestAct += str.at(k);
        k++;
    }
    if(tempTestAct != "-e" && tempTestAct != "-d" && tempTestAct != "-f"){
        tempTestArg = tempTestAct;
        tempTestAct = "-e";
    }else{
        k++;
        while(k < str.size()){
            tempTestArg += str.at(k);
            k++;
        }
    }
    return new Test(tempTestAct, tempTestArg);
}  
    bool newParse(string inp, commandComp* comp){
        int i = 0;
        bool start = true;
        vector<Input*> fillThis;
        while(i < inp.size()){
            LABELS:
            if(inp.at(i) == ';'){
                goto LABELSEMI;
            }
            if(inp.at(i) == '['){
                int k = i;
                while(k < inp.size() && inp.at(k) != ']'){
                    k++;
                }
                k -= i + 1;
                fillThis.push_back(makeTest_1(&i, inp.substr(i + 2, k - 2)));
                //cout << inp.substr(i + 1, k) << endl;
                i += k + 2;
            }
            if(i < inp.size() && inp.at(i) == '('){
                int k = i;
                while(k < inp.size() && inp.at(k) != ')'){
                    k++;
                }
                k -= i + 1;
                commandComp* nComp = new commandComp;
                newParse(inp.substr(i + 1, k), nComp);
                i += k + 2;
                fillThis.push_back(nComp);
            }
            if(i < inp.size() && inp.at(i) == ')'){
                i++;
            }
            if(i < inp.size() && inp.at(i) == ' '){// to skip spaces
                i++;
            }
            if(i < inp.size() && inp.at(i) == '#'){
                goto LABEL2;
            }
            if(i < inp.size() && (inp.at(i) == '&' || inp.at(i) == '|' || inp.at(i) == ';')){// this is to add connectors
                LABELSEMI:
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
            if(i < inp.size() && (inp.at(i) != '&' && inp.at(i) != '|' && inp.at(i) != ';' && inp.at(i) != ' ' && inp.at(i) != '#' && inp.at(i) != '(')){// parsing commandLeaf
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
                        if(tempAct == "exit"){
                            fillThis.push_back(new ExitObj());
                        }else{
                            fillThis.push_back(new commandLeaf(tempAct, empVec));
                        }
                        goto LABEL2;
                    }
                    else if(i < (inp.size() - 2) && (inp.at(i + 2) == '|' || inp.at(i + 2) == '&' || inp.at(i + 1) == ';')){
                        vector<string> empVec;
                        tempAct += inp.at(i);
                        i++;
                        if(tempAct.at(tempAct.size() - 1) == ' '){
                            tempAct.pop_back();
                        }
                        if(tempAct == "exit"){
                          fillThis.push_back(new ExitObj());
                        }else{
                          fillThis.push_back(new commandLeaf(tempAct, empVec));
                        }
                        goto LABELS;
                    }
                }//cout << tempAct << " <- this is tempAct" << endl;
                if(tempAct == "test"){
                    string tempStr = "";
                    i++;
                    while(i < inp.size() && inp.at(i) != ' '){
                        tempStr += inp.at(i);
                        i++;
                    }
                    i++;
                    tempStr += ' ';
                    if(tempStr != "-e" && tempStr != "-d" && tempStr != "-f"){
                        while(i < inp.size() && inp.at(i) != ' '){
                            tempStr += inp.at(i);
                            i++;
                        }
                    }
                    fillThis.push_back(makeTest_1(&i, tempStr));
                }else if(tempAct != "exit"){// creating exit if activity was not exit
                    string tempArg;
                    vector<string> tempStrVec;
                    if(inp.at(i + 1) == '"'){
                        i += 2;
                        while(i < inp.size() && inp.at(i) != '"'){
                              tempArg += inp.at(i);
                              i++;
                        }tempStrVec.push_back(tempArg);
                        i++;
                        //cout << "Made a quote" << endl;
                        goto LABELNAME;
                    }
                    while(i < inp.size() && inp.at(i) != '\0' && inp.at(i) != '&' && inp.at(i) != '|' && inp.at(i) != ';'){// parsing the arguments
                    //cout << "Through here" << endl;
                        if(inp.at(i) == ' '){
                            i++;
                        }tempArg = "";
                        if(i < inp.size() && inp.at(i) == '#'){
                            goto LABELNAME;
                        }
                        while( i < inp.size() && inp.at(i) != ' ' && inp.at(i) != '\0' && inp.at(i) != '&' && inp.at(i) != '|' && inp.at(i) != ';' && inp.at(i) != '#'){// goes through each word. Ends if there is a space or NULL
                            tempArg += inp.at(i);
                            i++;
                        }//cout << tempArg << endl;
                        if(tempArg != ""){// if tempArg is empty this means there is nothing to push
                            //cout << tempArg << " <- this is tempArg" << endl;
                            tempStrVec.push_back(tempArg);
                        }
                    }LABELNAME:
                    if(tempStrVec.size() != 0){// if the vector is empty there is nothing to push
                        //cout << "commandLeaf created" << endl;
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