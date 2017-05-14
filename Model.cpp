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
	if (simpleType)
		strncpy_s(this->data, data, 32);
	else
		addValue(data);
	//values.push_back(data);
}
void Model::setSimpleType(bool b)
{
	simpleType = b;
}
bool Model::isSimpleType()
{
	return simpleType;
}



void Model::write()
{
	if (typ == Model::Typ::Array) {
		std::cout << "TABLICA" << std::endl;
		std::cout << "\tTYPE:\t" << Type << std::endl;
		std::cout << "\tNAME:\t" << Name << std::endl;
		std::cout << "\tDATA:\t" << std::endl;
		for (unsigned i = 0; i < values.size(); ++i)
		{
			std::cout << "\t\t" << values[i] << std::endl;
		}
	}
	else if (typ == Model::Typ::Structure)
	{
		std::cout << "STRUKTURA:\t" << Name << std::endl;
		for (unsigned i = 0; i < fieldNames.size(); ++i)
		{
			std::cout << "\tNAME:\t" << fieldNames[i] << std::endl;
			std::cout << "\tTYPE:\t" << fieldTypes[i] << std::endl;
		}
	}
	else if (typ == Model::Typ::Var)
	{
		if(simpleType)
			std::cout << "ZMIENNA TYPU PROSTEGO" << std::endl;
		else
			std::cout << "ZMIENNA TYPU ZDEFINIOWANEGO" << std::endl;
		std::cout << "\tTYPE:\t" << Type << std::endl;
		std::cout << "\tNAME:\t" << Name << std::endl;

		if (simpleType)
			std::cout << "\tDATA:\t" << data << std::endl;
		else {
			std::cout << "\tDATA:\t" << std::endl;
			for(unsigned i=0; i<values.size(); ++i)
				std::cout << "\t\t" << values[i] << std::endl;
		}
	}
}