#ifndef CONNECTOR_H
#define CONNECTOR_H
#include <vector>
#include <unistd.h>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include "input.h"
using namespace std;

class Connector : public Input{
    private:
        string activity;
    public:
        bool execute(int* i){
        
        
        }

};


#endif