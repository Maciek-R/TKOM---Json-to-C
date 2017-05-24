#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <iostream>
#include <string>
#include <fstream>

class Model
{
private:
	char Type[32];
	char Name[32];//nazwa tablicy, nazwa typu struktury lub nazwa zmiennej
	std::vector<std::string> values;// wartoœci tablicy lub zmiennej strukturalnej
	
	//uzywane przez tablice przechowujace struktury
	std::vector<Model*> models;

	//uzywane przez strukture
	std::vector<std::string> fieldNames;
	std::vector<std::string> fieldTypes;

	//przez variable dla simple
	char data[32];
	bool simpleType;
public:
	enum Typ { Array, Structure, Var };
	Model::Typ typ;

	Model(Model::Typ);
	void addModel(Model*);
	int getModelSize();
	char * getName();
	std::string getFieldName(int);
	std::string getFieldType(int);
	int getFieldsAndTypesSize();

	void setType(char *);
	void setName(char *);
	void addValue(char *);


	void setStructTypeName(char*);
	void setStructFieldName(char*);
	void setStructFieldType(char*);

	void setVariableData(char*);
	void setSimpleType(bool);
	bool isSimpleType();

	void write(std::fstream &);
};

#endif