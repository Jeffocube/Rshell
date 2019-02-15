#ifndef PARSE_H
#define PARSE_H
#include <unistd.h>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include "input.h"
#include <sstream>
#include <cstring>
#include "command.h"
using namespace std;

void parse(string userInput, vector<Input*> outVector)
{
	int marker = 0;
	vector<string> commandStorage; //putting everything in her
	for (int i = 0; i < userInput.size(); i++)
	{
		if (userInput.at(i) == ';') // || userInput.at(i) == '|') 
		{
			string temp;
			temp = userInput.substr(marker, i - marker + 1);
			commandStorage.push_back(temp); temp.clear();

			marker = i+2; //assume next char is ' '
			i+=2;
			//notdone
		}//break into
		else if (userInput.at(i) == '&' || userInput.at(i) == '|')
		{
			if (i != userInput.size() - 1)
			{
				if (userInput.at(i+1) == userInput.at(i))
				{
					string temp;
					temp = userInput.substr(marker, i - marker + 2);
					commandStorage.push_back(temp); temp.clear();

					marker = i+3; i+=3; //extra 1 because two char connector
				}
			}
					
		}
	}


return;


	//create commandLeaf objects to place in outVector
	
	
}

#endif
