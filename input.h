#infdef INPUT_H
#define INPUT_H
#include <unistd.h>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

class input{
    public:
    virtual void execute();
};

#endif