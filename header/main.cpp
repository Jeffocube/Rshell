#include <iostream>
#include <vector>
#include <unistd.h>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "input.h"
#include "command.h"
using namespace std;

int main(){
	vector<string> newVec;
	newVec.push_back("hello");
	newVec.push_back("world");
	commandLeaf ncom = commandLeaf("echo", newVec);
	int* k = new int(1);
	ncom.execute(k);
	cout << "again2" << endl;
	exit(0);
}
