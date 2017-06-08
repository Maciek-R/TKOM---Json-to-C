#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class Object {
public:
	std::string name;

	Object() {}
	Object(std::string);

	virtual Object * clone() = 0;
	virtual void write(std::fstream&) = 0;
	virtual void writeField(std::fstream&) = 0;
	virtual void writeFieldValue(std::fstream&, std::string) = 0;
	virtual void writeArrayValue(std::fstream&, std::string) = 0;
	virtual void setValue(std::string) = 0;
	std::string getName();
};

#endif
