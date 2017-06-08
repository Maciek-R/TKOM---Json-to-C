#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include <iostream>

#include <vector>
#include <string>
#include <fstream>
#include "Structure.h"
#include "Array.h"
#include "SimpleType.h"


class ObjectManager
{
private:
	std::vector<std::string> declaredSimpleTypes;
	std::vector<Object*> objects;
	std::vector<Structure*> structures;

	Object* getType(std::string);
public:
	ObjectManager();

	void addStructureType(Structure*);
	bool existsStructureType(std::string);
	bool existsStructField(Structure*, std::string);
	void addStructureField(Structure*, std::string, std::string);

	void addSimpleTypeVariable(std::string, std::string, std::string);
	Structure* addStructureVariable(std::string, std::string);

	Array* addArrayVariable(std::string, std::string);
	void addToArraySimpleType(Array*, std::string);
	Structure* addToArrayStructure(Array*);

	bool existsType(std::string);
	bool isSimpleType(std::string);

	Structure* findStructureByType(std::string);
	Object* findStructureByField(Structure*, std::string);

	void writeAll(std::string);
};

#endif