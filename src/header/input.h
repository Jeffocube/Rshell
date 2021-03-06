#ifndef INPUT_H
#define INPUT_H
#include <unistd.h>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

class Input{
    private:
    public:
        virtual int execute(int ) = 0;
        virtual bool getPass() = 0;
        virtual bool setPass(bool, int) = 0;
        virtual string getActivity(int i) = 0;
        int in = 0;
        int out = 1;
};

#endif
