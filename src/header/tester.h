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

class Test : public Input{
    private:
        string activity;// -e and such
        string point;// directory or file we are looking up status for
        bool pass = false;
    public:
        int execute(int ){
            
        }
        bool getPass(){
            return pass;
        }
        bool setPass(bool p, int i){
            pass = p;
        }
        string getActivity(int i){
            return "test";
        }
    
};