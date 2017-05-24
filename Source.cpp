#include "Source.h"

Source::Source() 
{
	
	plik.open("ABC.txt", std::ios::in);
	string line;

	while (getline(plik, line)) {
		jsonString += line;
		jsonString += '\n';
	}
	plik.close();
	this->line = 1;
}

string Source::getStringFromFile()
{
	return jsonString;
}

char Source::nextChar()
{
	++i;
	return jsonString[i];
	/*if (i < test.length()) {
		c = test[i];
		return true;
	}
	else {
		return false;
	}*/
}
bool Source::isWhiteChar(char x) {
	if (x == ' ' || x == '\t')
		return true;
	else if (x == '\n')
	{
		++line;
		return true;
	}
	else
		return false;
}

bool Source::isDigit(char x)
{
	if (x >= '0' && x <= '9')
		return true;

	if (x >= 'a' && x <= 'z' || x >= 'A' && x <= 'Z')
		return true;

	if (x == '"')
		return true;

	return false;
}