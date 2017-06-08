#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include <iostream>

#include <vector>
#include "Model.h"
#include <string>
#include <fstream>
#include "Structure.h"
#include "Array.h"
#include "SimpleType.h"
//#include "Var.h"
//#include "Structure.h"


class ObjectManager
{
private:
	std::vector<std::string> declaredSimpleTypes;
	std::vector<std::string> declaredOwnTypes;

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
/*private:
	std::vector<Model*> models;
	std::vector<std::string> declaredSimpleTypes;
	std::vector<std::string> declaredOwnTypes;
public:
	ObjectManager();
	void addModel(Model*);

	void addArray();
	void setType(char*);
	void setName(char*);
	void addArrayValue(char*);


	void addStructDeclaration();
	void setStructTypeName(char*);
	void setStructFieldName(char*);
	void setStructFieldType(char*);
	Model* getStructureWithTypeName(std::string);

	void addVariable();
	void setVariableData(char*);
	bool isSimpleType();

	void writeAll(std::string);

	bool checkIfTypeIsExisting(std::string);
	void addNewType(std::string);*/
};

#endif