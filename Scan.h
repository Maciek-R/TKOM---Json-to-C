#ifndef SCAN_H
#define SCAN_H

#include <iostream>

#include "Source.h"

class Scan
{
	private:
		Source * source;
		char c;
		char spell[32];
		int tab = 0;
	public:
		enum Type { Object, Array, Value, String, Number, Comma, EndObject, EndArray, Error };
		Scan(Source *);
		Type nextSymbol();
		void nextChar();
		char * getSpell();


		void setSpaces();
};

#endif