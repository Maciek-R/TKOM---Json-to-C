#ifndef PARSER_H
#define PARSER_H

#include "Scan.h"
#include "ObjectManager.h"
#include <conio.h>
#include <vector>
#include "Tree.h"

class Parser
{
private:
	Scan * scan;
	Scan::Type sym;
	char * spell;
	int tab = 0;
	ObjectManager objectManager;
	
	enum class VARTYPE {None, Array, Var, Struct};
	VARTYPE vartype = VARTYPE::None;

	enum class Expected {None, Type, Name, Value, Values, Fields, StructTypeName, FieldName, FieldType, FieldTypeName, DataValue, Colon, Object, WordName, WordValues, WordValue, WordFields, WordAttrib, WordType, Data, WordData};
	Expected expected=Expected::None;
	std::vector <Scan::Type> exps;
	std::vector <string> expsString;

	void serveNewType();
	void serveArray();
	void serveStruct();
	void serveVar();
public:
	
	Parser(Scan*);
	void start();
	void nexts();

	void setSpaces();
};

#endif