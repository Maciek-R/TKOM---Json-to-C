#include "SimpleType.h"

SimpleType::SimpleType(SimpleType* simpleType)
{
	this->val = simpleType->val;
	this->type = simpleType->type;
	this->name = simpleType->name;
}
SimpleType::SimpleType(std::string type)
{
	this->type = type;
}

SimpleType* SimpleType::clone() 
{
	return new SimpleType(this);
}

void SimpleType::setValue(std::string value)
{
	this->val = value;
}

void SimpleType::writeField(std::fstream &file)
{
	file << type << " " << name << ";";
}

void SimpleType::write(std::fstream& file)
{
	file << name << " = " << val << ";\n";
}
void SimpleType::writeFieldValue(std::fstream& file, std::string pref)
{
	file << pref << name + " = " + val + ";\n";
}

void SimpleType::writeArrayValue(std::fstream& file, std::string pref)
{
	file << pref << " = " << this->val << ";\n";
}
