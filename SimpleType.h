#ifndef SIMPLE_TYPE_H
#define SIMPLE_TYPE_H

#include <fstream>
#include "Object.h"

class SimpleType : public Object {
public:

	SimpleType(SimpleType*);
	SimpleType(std::string value);

	SimpleType* clone();
	std::string value;//int char, double, itp.

	void write(std::fstream&);
	void SimpleType::writeField(std::fstream&);
};

#endif
