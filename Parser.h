#ifndef PARSER_H
#define PARSER_H

#include "Scan.h"
#include "ObjectManager.h"

class Parser
{
private:
	Scan * scan;
	Scan::Type sym;
	char * spell;
	int tab = 0;
	ObjectManager objectManager;
	
	enum Expected {None, Type, Name, Value, Values, Fields, StructTypeName, FieldName, FieldType, FieldTypeName, DataValue };
	Expected expected=None;
public:
	
	Parser(Scan*);
	void start();
	void nexts();

	void setSpaces();
};

#endif