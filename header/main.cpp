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
#include "connector.h"
using namespace std;

int main(){
	vector<string> newVec;
	vector<string> nvec;
	nvec.push_back("hello");
	newVec.push_back("hello");
	newVec.push_back("world");
	commandComp cc = commandComp();
	commandLeaf ncom = commandLeaf("echo", newVec);
	commandLeaf nco = commandLeaf("echo", nvec);
	Connector ncon = Connector("||", &cc);
	vector<Input*> tempIn;
	tempIn.push_back(&ncom);
	tempIn.push_back(&ncon);
	tempIn.push_back(&nco);
	cc.setVec(tempIn);
	cc.execute(1);
	exit(0);
}
