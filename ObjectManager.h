#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include <iostream>

#include <vector>
#include "Model.h"
#include "Array.h"
//#include "Var.h"
//#include "Structure.h"


class ObjectManager
{
private:
	std::vector<Model*> models;
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

	void writeAll();
};

#endif