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
#include "exit.h"
#include "newParse.h"
using namespace std;

int main(){
	while(1){
		string input;
		int i = 1;
		commandComp* command = new commandComp;
		do{
			cout << "$ ";
			getline(cin, input);
		}while(newParse(input, command));
		command->execute(i);
	}
	exit(0);
}
