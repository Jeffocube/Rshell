#ifndef EXIT_H
#define EXIT_H
#include <vector>
#include <unistd.h>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "input.h"
using namespace std;

class Exit : public Input{
    public:
    Exit(){ }
    int execute(int i){
        // cout << "Hello4" << endl;
        exit(0);
    }
    bool getPass(){
        return true;
    }
    
};


#endif