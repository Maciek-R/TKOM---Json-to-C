#ifndef SOURCE_H
#define SOURCE_H

#include<fstream>
#include<string>

using namespace std;

class Source
{
private:
	std::fstream plik;
	string jsonString;
	int i = -1;
public:
	Source(std::string inputFile);
	string getStringFromFile();

	char nextChar();
	bool isWhiteChar(char x);
	bool isDigit(char x);
	int  line;
};

#endif