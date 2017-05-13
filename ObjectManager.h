#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include <iostream>

#include <vector>
#include "Model.h"
#include "Array.h"
#include <string>
//#include "Var.h"
//#include "Structure.h"


class ObjectManager
{
private:
	std::vector<Model*> models;
	std::vector<std::string> declaredSimpleTypes;
	std::vector<std::string> declaredOwnTypes;
public:
	ObjectManager();

	void addArray();
	void setType(char*);
	void setName(char*);
	void addArrayValue(char*);


	void addStructDeclaration();
	void setStructTypeName(char*);
	void setStructFieldName(char*);
	void setStructFieldType(char*);

	void addVariable();
	void setVariableData(char*);
	bool isSimpleType();

	void writeAll();

	bool checkIfTypeIsExisting(std::string);
	void addNewType(std::string);
};

#endif