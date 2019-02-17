#include <unistd.h>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
using namespace std;
int main(int argc, char** argv){

      //fork prototype
	pid_t childPid;
    int status;
	childPid = fork();
	if(childPid == 0){
		exit(1);
	}else{
		waitpid(childPid, &status, 0);
		cout << status << endl;
	}
	
	 char argv[3];
    string string1;
    string string2;
    cin >> string1;
    cin >> string2;
    char str1 = &string1[0u];
    char* str2 = &string2[0u];
    argv[0] = str1;
    argv[1] = str2;
    argv[2] = NULL;
    execvp(argv[0] , argv );
	
    return 0;
}
