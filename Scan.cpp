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
		} while (source->isWhiteChar(c));

		if (c == '{') {
			
			return Object;
		}
		if (c == '"') {	// String
			int len = 0;
			do {
				
				nextChar();
				spell[len++] = c;
				
				if (c == '\n') {
					std::cout << "Missing \"? Line: " << getLine() << std::endl;
					_getch();
					exit(0);
				}

			} while (c != '"');

			spell[--len] = '\0';

			return String;
		}

		if (c == ':') {
			return Value;
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
}

char * Scan::getSpell()
{
	return spell;
}
void Scan::nextChar()
{
	c = source->nextChar();
}
int Scan::getLine()
{
	return source->line;
}