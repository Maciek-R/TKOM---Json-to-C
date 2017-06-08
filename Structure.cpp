#include "Structure.h"

Structure::Structure(std::string type)
{
	structType = type;
}
Structure::Structure(Structure* structure)
{
	this->name = structure->name;
	this->structType = structure->structType;

	for (Object * obj : structure->fields)
		this->fields.push_back(obj->clone());
	

}

void Structure::setValue(std::string) {};

std::string Structure::getStructType()
{
	return structType;
}

Structure* Structure::clone()
{
	return new Structure(this);
}

void Structure::writeDeclaration(std::fstream& file)
{
	file << "typedef struct\n{ " << std::endl;
	for (int i = 0; i < fields.size(); ++i) {
		file << "\t";
		fields[i]->writeField(file);
		file << "\n";
	}
	file << "} " << structType << ";\n";
}
void Structure::writeField(std::fstream& file)
{
	file << structType << " " << name << ";";
}

void Structure::write(std::fstream& file)
{
	file << structType << " " << name << ";" << std::endl;
	writeFieldValue(file, "");
}
void Structure::writeFieldValue(std::fstream& file, std::string pref) {
	for (int i = 0; i < fields.size(); ++i) 
	{
		std::string nestedPref = pref + name + ".";
		fields[i]->writeFieldValue(file, nestedPref);
	}
}