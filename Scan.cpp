#include "Scan.h"

Scan::Scan(Source * source)
{
	this->source = source;
}

Scan::Type Scan::nextSymbol() {
		do {
			nextChar();
			if (c == '\0') {
				return Error;
			}
		} while (source->isSpace(c));

		if (c == '{') {
			
			return Object;
		}
		if (c == '"') {	// String
			int len = 0;
			do {
				
				nextChar();
				spell[len++] = c;
				//tu obsluga bledu gdy brakuje "
				//if (c == '\n') {
//
	//			}

			} while (c != '"');

			spell[--len] = '\0';

			return String;
		}

		if (c == ':') {
			return Value;
		}
		if (source->isDigit(c) || c == '-') {
			int len = 0;
			do {
				spell[len++] = c;
				nextChar();
			} //while (c != ' ');
			while (source->isDigit(c));

			spell[--len] = '\0';

			return Number;
		}
		if (c == '[') {
			
			return Array;
		}
		if (c == ',')
			return Comma;

		if (c == '}') {
			
			return EndObject;
		}
		if (c == ']') {
			
			return EndArray;
		}




		//	while (isCharOrDigit(c))
		//	nextChar();





	
}

char * Scan::getSpell()
{
	return spell;
}

void Scan::nextChar()
{
	c = source->nextChar();
}

void Scan::setSpaces()
{
	for (int q = 0; q < tab; ++q)
		cout << '\t';
}