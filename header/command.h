#ifndef COMMAND_H
#define COMMAND_H
#include <unistd.h>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <input.h>
using namespace std;

class command : public input{
    private:
    enum connector; 
};
#endif