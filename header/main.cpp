#include <iostream>
#include "parse.h"

using namespace std;

int main()
{
//testing shit
	string input;
//	cout << "cin an input string " << endl;
//	cin >> input;
	cout << endl;

	vector<Input*> irrelevant4now;
	input = "hello I like apples; I like apples && oranges; Testtest || 123 test test ; testing, dont  think last one shows yet though";
	parse(input, irrelevant4now);
}
