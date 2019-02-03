#include <iostream>
#include <string>
#include <unistd.h>
using namespace std;

int main()
{
	
	//fork prototype
	cout << "fork prototype" << endl;
	pid_t testpid = fork();

	cout << "testpid = " << testpid << endl;

	cout << "testing raw fork" << endl;
	cout << fork() << endl;
	return 0;
}
