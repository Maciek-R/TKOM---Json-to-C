#ifndef TOKENTYPE_H
#define TOKENTYPE_H
#include "Scan.h"


class TokenType
{
protected:
	bool simpleToken;
	bool anyTokenLeft;

public:
	TokenType();
	bool isSimpleToken();

	virtual void add(TokenType *);
	virtual bool isAnyTokenLeft();
	virtual Scan::Type getNext() = 0;
	virtual TokenType* next();
};

#endif