#include "Model.h"


Model::Model(Model::Typ t)
{
	typ = t;
}
void Model::addModel(Model*m)
{
	models.push_back(m);
}
int Model::getModelSize()
{
	return models.size();
}
char* Model::getName()
{
	return this->Name;
}
std::string Model::getFieldName(int x)
{
	return this->fieldNames[x];
}
std::string Model::getFieldType(int x)
{
	return this->fieldTypes[x];
}
int Model::getFieldsAndTypesSize()
{
	return this->fieldNames.size();
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



void Model::write(std::fstream & file)
{
	if (typ == Model::Typ::Array) {
		/*std::cout << "TABLICA" << std::endl;
		std::cout << "\tTYPE:\t" << Type << std::endl;
		std::cout << "\tNAME:\t" << Name << std::endl;
		std::cout << "\tDATA:\t" << std::endl;
		if (simpleType)
		{
			for (unsigned i = 0; i < values.size(); ++i)
			{
				std::cout << "\t\t" << values[i] << std::endl;
			}
		}
		else
		{
			for (unsigned i = 0; i < models.size(); ++i)
			{
				models[i]->write();
			}
		}*/

		if (simpleType)
		{
			file << Type << " " << Name << "[" << values.size() << "];\n";
			for (unsigned i = 0; i < values.size(); ++i)
			{
				file << Name << "[" << i << "] = " << values[i] << ";" << std::endl;
			}
		}
		else
		{
			file << Type << " " << Name << "[" << models.size() << "];\n";
			for (unsigned i = 0; i < models.size(); ++i)
			{
				
				for (int j = 0; j < models[i]->getFieldsAndTypesSize(); ++j)
				{
					file << Name << "[" << i << "].";
					file << models[i]->getFieldType(j) << " = " << models[i]->getFieldName(j) << ";\n";
				}
			}
		}
		file << "\n";
	}
	else if (typ == Model::Typ::Structure)
	{
		/*std::cout << "STRUKTURA:\t" << Name << std::endl;
		for (unsigned i = 0; i < fieldNames.size(); ++i)
		{
			std::cout << "\tNAME:\t" << fieldNames[i] << std::endl;
			std::cout << "\tTYPE:\t" << fieldTypes[i] << std::endl;
		}*/
		file << "typedef struct " << Name <<"\n";
		file << "{\n";
		for (unsigned i = 0; i < fieldNames.size(); ++i)
		{
			file << "\t" << fieldTypes[i] << " " << fieldNames[i] << ";\n";
		}
		file << "}\n";
	}
	else if (typ == Model::Typ::Var)
	{
		/*if(simpleType)
			std::cout << "ZMIENNA TYPU PROSTEGO" << std::endl;
		else
			std::cout << "ZMIENNA TYPU ZDEFINIOWANEGO" << std::endl;
		std::cout << "\tTYPE:\t" << Type << std::endl;
		std::cout << "\tNAME:\t" << Name << std::endl;

		if (simpleType)
			std::cout << "\tDATA:\t" << data << std::endl;
		else {
			std::cout << "\tDATA:\t" << std::endl;
			for (unsigned i = 0; i < fieldTypes.size(); ++i)
			{
				std::cout << "\t\t" << fieldTypes[i] <<"\t" << fieldNames[i] << std::endl;
			}
		}*/


		if (simpleType)
		{
		
			file << Type;
			file << " " << Name;
			file << " = " << data << ";" << std::endl;
		}
		else 
		{
			file << Type;
			file << " " << Name << ";\n";
			for (unsigned i = 0; i < fieldTypes.size(); ++i)
			{
				file << Name << "." << fieldTypes[i] << " = " << fieldNames[i] << ";"<< std::endl;
			}
		}
		file << "\n";
	}
}