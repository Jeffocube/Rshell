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
	//testing userinput is in here properly
	cout << "userinput size is : " << userInput.size() << endl;

	int marker = 0;
	vector<string> commandStorage; //putting everything in here
	for (int i = 0; i < userInput.size(); i++)
	{
		if (userInput.at(i) == ';') // || userInput.at(i) == '|') 
		{
			string temp;
			temp = userInput.substr(marker, i - marker + 1);
			commandStorage.push_back(temp); temp.clear();

			marker = i+2; //assume next char is ' '
			i+=2;
		
		}
		//OPTIONAL? check to make sure & is paired with another &, | is paired with another |? this is set assuming & is always && etc.
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



	//use the strings (commands and connectors) in commandStorage to
	//create commandLeaf objects to place in outVector
		
	//output to check vector
	cout << "commandstorage has " << commandStorage.size() << " elements." << endl;
	cout << "testing vector output: " << endl;
	for (int i = 0; i < commandStorage.size(); ++i)
	{
		cout << "storage vector at " << i << " is : " << commandStorage.at(i) << endl;
	}

	//made a vector of strings now to parse within the strings(cmd,arg,connector)
	
	for (int i = 0; i < commandStorage.size(); ++i)
	{
		//first separate the first word (should be command)
		string temp = "";
		vector<string> args;
		int marker = 0;
		for (marker = 0; marker < commandStorage.at(i).size(); ++marker)//each string in storage
		{
			if (marker == commandStorage.size() - 1)
			{	
				//if string is 1 word no space no connector (last cmd for ex)
				temp = commandStorage.at(i);
//				Input* tempI = new commandLeaf(temp, args); //args will be empty. maybe make 1param constructor?
				//commented out until constructor is made (and/or input.h is implemented)
				break;
			}
			else if (commandStorage.at(i).at(marker) == ' ')
			{
				temp = commandStorage.at(i).substr(0, marker); //get command
				string temp2;

				//make temp2 everything without the first word and without the connector at the end

				if (commandStorage.at(i).at(commandStorage.at(i).size() - 1) == ';')
				{
					temp2 = commandStorage.at(i).substr(marker, commandStorage.at(i).size() - 2);
					
					char connector = commandStorage.at(i).at(commandStorage.at(i).size() - 1);
					
				
					//I guess parse the temp substring into vector of strings to match constructor of commandLeaf
					
					for (int x = 0; x < temp2.size(); ++x)
					{
						
				}
			}
		}	
		cout << "commandstorage . at (i) = " << temp << endl;
	}	

}

#endif
