#ifndef PARSER_H
#define PARSER_H

#include "Scan.h"
#include "ObjectManager.h"
#include <conio.h>
#include <vector>


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

	enum class Expected {None, Type, Name, Value, Values, Fields, StructTypeName, FieldName, FieldType, FieldTypeName, DataValue, Colon, Object, WordName, WordValues, WordValue, WordFields, WordAttrib, WordType, Data, WordData, NextField, NextDataValue};
	Expected expected=Expected::None;
	//std::vector <Scan::Type> exps;
	std::vector <string> expsString;
	void write(Scan::Type tmp);
	void error(Scan::Type, Scan::Type);

	void serveVar();

	void accept(Scan::Type);
	void acceptNext(Scan::Type);
	void acceptNext(Scan::Type, const char *);
	void acceptModule();
	void acceptNewObject();
	void acceptNewObjectType();
	void acceptNewStructure();
	void acceptNewElementOfStructure();

	void acceptNewArray(bool);
	void acceptNewElementOfSimpleArray();
	void acceptNewElementOfComplexArray();
	void acceptNewElementStructInArray(Model *);
	void acceptNewStructInArray();

	void acceptNewVariable(std::string);
	void acceptNewElementOfVariable(std::string, bool);
public:
	
	Parser(Scan*);
	void start();
	void nexts();

	void setSpaces();
	void writeAllToFile(std::string outputFile);
};

#endif