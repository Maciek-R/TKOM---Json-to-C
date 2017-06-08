#ifndef SCAN_H
#define SCAN_H

#include <iostream>
#include <conio.h>
#include "Source.h"

class Scan
{
	private:
		Source * source;
		char c;
		char spell[128];
	public:

		enum Type { Object, Array, Value, String, Number, Comma, EndObject, EndArray, Error, END_FILE, None};
		Scan(Source *);
		Type nextSymbol();
		void nextChar();
		char * getSpell();
		int getLine();

};

#endif