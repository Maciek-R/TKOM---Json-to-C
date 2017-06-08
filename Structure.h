#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "Object.h"

class Structure : public Object 
{
public:
	std::string structType;
	std::vector<Object *> fields;

	Structure(std::string);
	Structure(Structure*);

	Structure* clone();
	std::string getStructType();

	void setValue(std::string);
	bool isInitialized();

	void writeDeclaration(std::fstream&);
	void writeField(std::fstream&);
	void writeFieldValue(std::fstream&, std::string);
	void writeArrayValue(std::fstream&, std::string);

	void write(std::fstream&);
};

#endif
