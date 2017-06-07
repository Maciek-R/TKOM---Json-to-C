#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "Object.h"
#include <string>

class Structure:public Object 
{
public:
	std::string structType;
	std::vector<Object *> fields;

	Structure(std::string);
	Structure(Structure*);

	Structure* clone();
	std::string getStructType();



	void writeDeclaration(std::fstream&);
	void writeField(std::fstream&);
	void write(std::fstream&);
};

#endif
