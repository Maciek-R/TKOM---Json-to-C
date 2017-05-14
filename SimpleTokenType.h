#ifndef SIMPLE_TOKEN_TYPE_H
#define SIMPLE_TOKEN_TYPE_H
#include "TokenType.h"

class SimpleTokenType: public TokenType
{
private:
	Scan::Type type;
public:
	SimpleTokenType(Scan::Type);
	Scan::Type getNext(TokenType*);

	bool isAnyTokenLeft();

	void write(int);
};

#endif SIMPLE_TOKEN_TYPE_H