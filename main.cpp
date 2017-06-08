#include <iostream>
#include <string>
#include <conio.h>
#include <vector>
#include <fstream>

#include "Source.h"
#include "Scan.h"
#include "Parser.h"
using namespace std;


int main(int argc, char *argv[]) {
	if (argc < 3) {
		std::cout << "Need 2 arguments: input and output file!" << std::endl;
		_getch();
		return -1;
	}
	string inputFile = argv[1];
	string outputFile = argv[2];

	Source * source = new Source(inputFile);
	Scan * scan = new Scan(source);
	Parser * parser = new Parser(scan);

	parser->start();

	parser->writeAllToFile(outputFile);
	std::cout << "See " << outputFile << " file." << std::endl;

	_getch();
	return 0;
}
