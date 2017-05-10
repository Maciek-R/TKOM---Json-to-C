#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <iostream>
#include <string>

class Model
{
private:
	char Type[32];
	char Name[32];//nazwa tablicy albo nazwa typu struktury
	std::vector<std::string> values;
	
	//uzywane przez strukture
	std::vector<std::string> fieldNames;
	std::vector<std::string> fieldTypes;
	

	//przez variable
	char data[32];
public:
	enum Typ { Array, Structure, Var };
	Model::Typ typ;

	Model(Model::Typ);

	void setType(char *);
	void setName(char *);
	void addValue(char *);


	void setStructTypeName(char*);
	void setStructFieldName(char*);
	void setStructFieldType(char*);

	void setVariableData(char*);

	void write();
};

#endif