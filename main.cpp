#include <iostream>
#include <string>
#include <conio.h>
#include <vector>
#include <fstream>

#include "Source.h"
#include "Scan.h"
#include "Parser.h"
using namespace std;

bool isString(string str);
bool isChar(char x);
bool isNumber(string s);
bool isInt(string s);
bool isIntFrac(string s);
bool isDigit(char x);
void skipWhiteChars(string str, int &i);




bool isPair(string str);


bool nextChar();


int i = -1;



string test;
char c;



//Type nextSymbol();

int main() {

	
	Source * source = new Source();
	Scan * scan = new Scan(source);
	Parser * parser = new Parser(scan);

	parser->start();
	

	_getch();
	return 0;
}
bool isChar(char x) 
{
	if (x == '\"')
		return false;
	return true;
}

bool isString(string str) 
{
	

	int i = 0;
	
	while (str[i] == ' ')
	{
		++i;
	}

	if (str[i] != '\"')
	{
		return false;
	}
	++i;

	while (isChar(str[i]))
	{
		++i;
	}

	if (str[i] != '\"') {
		return false;
	}


	return true;

}

bool isNumber(string str) {

	if (isInt(str))
	{
		return true;
	}

	if (isIntFrac(str)) {
		return true;
	}
	return false;

}

bool isInt(string str) {
	int i = 0;

	skipWhiteChars(str, i);

	if (str[i] == '-')
		++i;

	while (isDigit(str[i])) {
		++i;
		//cout << "znak" << endl;
	}

	skipWhiteChars(str, i);

	if (i == str.length())
		return true;
	else {
		return false;
	}

}
bool isDigit(char x)
{
	if (x >= '0' && x <= '9') {
		return true;
	}
	else {
		return false;
	}
}

bool isIntFrac(string str) {
	int i = 0; 
	skipWhiteChars(str, i);

	if (str[i] == '-')
		++i;
	while (isDigit(str[i]))
		++i;

	if (str[i] != ',')
		return false;
	++i;
	while (isDigit(str[i]))
		++i;

	skipWhiteChars(str, i);

	if (i == str.length())
		return true;
	else
		return false;
}

void skipWhiteChars(string str, int &i) {

	while (str[i] == ' ') {
		++i;
		//cout << i << endl;
	}
}

bool isPair(string str)
{
	int i = 0;
	skipWhiteChars(str, i);

	return true;
}

bool isSpace(char x) {
	if (x == ' ' || x == '\t')
		return true;
	else
		return false;
}
bool isCharOrDigit(char x)
{
	if (x >= '0' && x <= '9')
		return true;

	if (x >= 'a' && x <= 'z' || x >= 'A' && x <= 'Z')
		return true;

	if (x == '"')
		return true;

	return false;
}
/*Type nextSymbol()
{
	do {
		if (nextChar() == false) {
			return Error;
		}
	} while (isSpace(c));

		if (c == '{')
			return Object;
		
		

		if (c == '"') {	// String

			do {
				nextChar();
			} while (c != '"');
				
			return String;
		}

		if (c == ':') {
			return Value;
		}
		if (isDigit(c) || c=='-') {

			do {
				nextChar();
			} while (c != ' ');

			return Number;
		}
		if (c == '[')
			return Array;

		if (c == ',')
			return Comma;

		if (c == '}')
			return EndObject;
		if (c == ']')
			return EndArray;

		



	//	while (isCharOrDigit(c))
		//	nextChar();



		

}
*/
