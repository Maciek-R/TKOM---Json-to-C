#ifndef ARRAY_H
#define ARRAY_H

#include "Object.h"

class Array : public Object {
public:

	Object *type;
	std::vector<Object *> elements;

	Array(Array *arr);
	Array(Object*, std::string);
	Array* clone();

	void write(std::fstream&);
	void writeField(std::fstream&);
	void writeFieldValue(std::fstream&, std::string);
	void writeArrayValue(std::fstream&, std::string);
	void setValue(std::string);

};
#endif