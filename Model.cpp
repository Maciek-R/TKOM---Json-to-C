#include "Model.h"


Model::Model(Model::Typ t)
{
	typ = t;
}

void Model::setType(char * type)
{
	strncpy_s(Type, type, 32);
}
void Model::setName(char * name)
{
	strncpy_s(Name, name, 32);
}
void Model::addValue(char * value)
{
	std::string s(value);
	values.push_back(s);
}


void Model::setStructTypeName(char * structTypeName)
{
	strncpy_s(Name, structTypeName, 32);
}

void Model::setStructFieldName(char* structFieldName)
{
	std::string s(structFieldName);
	fieldNames.push_back(s);
}
void Model::setStructFieldType(char* structFieldType)
{
	std::string s(structFieldType);
	fieldTypes.push_back(s);
}




void Model::setVariableData(char* data)
{
	strncpy_s(this->data, data, 32);
}



void Model::write()
{
	if (typ == Model::Typ::Array) {
		std::cout << Type << std::endl;
		std::cout << Name << std::endl;

		for (unsigned i = 0; i < values.size(); ++i)
		{
			std::cout << "\t" << values[i] << std::endl;
		}
	}
	else if (typ == Model::Typ::Structure)
	{
		std::cout << Name << std::endl;
		for (unsigned i = 0; i < fieldNames.size(); ++i)
		{
			std::cout << "\t" << fieldNames[i] << std::endl;
			std::cout << "\t" << fieldTypes[i] << std::endl;
		}
	}
	else if (typ == Model::Typ::Var)
	{
		std::cout << Type << std::endl;
		std::cout << Name << std::endl;
		
		std::cout << data << std::endl;
	}
}