#ifndef SIMPLE_TYPE_H
#define SIMPLE_TYPE_H

#include <fstream>
#include "Object.h"

class SimpleType : public Object {
public:
	std::string type;//int char, double, itp.
	std::string val;

	SimpleType(SimpleType*);
	SimpleType(std::string type);

	SimpleType* clone();
	void setValue(std::string);

	void write(std::fstream&);
	void writeField(std::fstream&);
	void writeFieldValue(std::fstream&, std::string);
	void writeArrayValue(std::fstream&, std::string);
};

#endif
