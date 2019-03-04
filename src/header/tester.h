#ifndef TESTER_H
#define TESTER_H
#include <unistd.h>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include "input.h"
#include <sys/types.h>
#include <sys/stat.h>
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
        Test(string activity, string point){
            this->activity = activity;
            this->point = point;
        }
        int execute(int i){
            cout << activity << "<-This is activity" << endl;
            cout << point << "<-This is point"<< endl;

	    
            struct stat stat0;

            int checke = stat(point.c_str(), &stat0);

            if (checke != 0)
            {
                cout << "(False)" << endl;
            }
            else if (activity == "-f")
            {
                if (stat0.st_mode & S_IFREG)
                {
                    cout << "(True)" << endl;
                }
            }
            else if (activity == "-d")
            {
                if (stat0.st_mode & S_IFDIR)
                {
                    cout << "(True)" << endl;
                }
                else
                {
                    cout << "(False)" << endl;
                }
            }
            else
            {
                cout << "(True)" << endl;
            }
            return i;
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
#endif
