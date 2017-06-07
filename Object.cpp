#include "Object.h"

Object::Object(std::string name)
{
	this->name = name;
}
std::string Object::getName()
{
	return name;
}