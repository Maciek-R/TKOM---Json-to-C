#ifndef PARSER_H
#define PARSER_H

#include "Scan.h"
#include "ObjectManager.h"
#include <conio.h>
#include <vector>
#include "Structure.h"


class Parser
{
private:
	Scan * scan;
	Scan::Type sym;
	char * spell;
	ObjectManager objectManager;

	std::vector <string> expsString;
	void writeToken(Scan::Type tmp);
	void Parser::printError(std::string);
	void error(Scan::Type, Scan::Type);

	void accept(Scan::Type);
	void acceptNext(Scan::Type);
	void acceptNext(Scan::Type, const char *);
	void acceptModule();
	void acceptModuleArray();
	void acceptNewObjects();
	bool acceptNewObject();
	void acceptSequenceName();
	void acceptSequenceFields(Structure*);
	bool acceptSequenceField(Structure*);

	void acceptArray();
	void acceptArrayElements(Array*);
	bool acceptArrayElement(Array*);

	void acceptVar();
	void acceptVarStructure(Structure*);
	void acceptVarStructureValues(Structure*);
	bool acceptVarStructureValue(Structure*);
	
public:
	
	Parser(Scan*);
	void start();
	void nexts();

	void writeAllToFile(std::string outputFile);
};

#endif