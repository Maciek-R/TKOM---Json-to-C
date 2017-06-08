#include "Array.h"

Array::Array(Array *arr)
{
	this->name = arr->name;
	this->type = arr->type;

	for (Object* obj : arr->elements)
		this->elements.push_back(obj->clone());
}

Array::Array(Object* type, std::string name)
{
	this->name = name;
	this->type = type;
}

Array* Array::clone() {
	return new Array(this);
}

void Array::write(std::fstream& file) 
{
	//strm << m_type->getTypeOutput() << " " << m_variableName << "[" << m_elements.size() << "];" << std::endl;
	file << this->type->name<< " " << name << "[" << elements.size() << "];\n";
	for (int i = 0; i < elements.size(); ++i) 
	{
		std::string pref = name + "[" + std::to_string(i) + "]";
		elements[i]->writeArrayValue(file, pref);
	}
}

void Array::writeField(std::fstream& file) 
{}
void Array::writeFieldValue(std::fstream& file, std::string pref) 
{}
void Array::writeArrayValue(std::fstream& file, std::string pref)
{}
void Array::setValue(std::string value)
{}
bool Array::isInitialized()
{
	return !elements.empty();
}