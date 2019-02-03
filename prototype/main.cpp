#include <unistd.h>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;
int main(int argc, char** argv){

      //fork prototype
 
    int status;
      pid_t testpid = fork();
      cout << "pid_t = testpid = fork();" << endl;
      

    execvp(argv[1] , argv + 1);
    cout << "execvp argv[1] argv + 1;" << endl;


    waitpid(testpid, &status, 0);
	cout << "waitpid created with testpid " << endl;

      //cout << "testpid = " << testpid << endl;

      //cout << "testing raw fork" << endl;

      //cout << fork() << endl;
    //execvp prototype
    execvp(argv[1] , argv + 1);
	cout << "execvp argc1, argv + 1; " << endl;


	if (testpid == -1)
	{
		cout << "-1 error" << endl;
	}
	if (testpid == 0)
	{
		cout << "0, successfully forked back " << endl;
	}
	if (testpid > 0)
	{
		cout << "child process starts" << endl;
	}


	cout << "end of program, testpid = " << testpid << endl;
    return 0;
}
