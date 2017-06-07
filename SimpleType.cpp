#include "SimpleType.h"

SimpleType::SimpleType(SimpleType* simpleType)
{
	this->value = simpleType->value;
	this->name = simpleType->name;
}
SimpleType::SimpleType(std::string value)
{
	this->value = value;
}

SimpleType* SimpleType::clone() 
{
	return new SimpleType(this);
}

void SimpleType::writeField(std::fstream &file)
{
	file << value << " " << name << ";";
}

void SimpleType::write(std::fstream& file)
{
	file << name << " = " << value << ";\n";
}