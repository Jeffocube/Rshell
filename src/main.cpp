#include <iostream>
#include <vector>
#include <unistd.h>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "header/input.h"
#include "header/command.h"
#include "header/connector.h"
#include "header/exit.h"
#include "header/newParse.h"
#include "header/tester.h"
using namespace std;
int main(){
	while(1){
		string input;
		int i = 1;
		commandComp* command = new commandComp();
		do{
			cout << "$ ";
			getline(cin, input);
		}while(newParse(input, command));
		command->execute(i);
	}
	exit(0);
}
