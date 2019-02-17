#include <vector>
#include <unistd.h>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "command.h"
#include "helpers.h"
#include "exit.h"
#include "input.h"

using namespace std;
int main(){
    exit* ex = new exit();
    vector<Input*> tempVec;
    tempVec.push_back(ex);
    commandComp command = commandComp(tempVec);
    
    return 0;
}