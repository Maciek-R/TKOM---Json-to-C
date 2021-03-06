#ifndef COMPLEX_TOKEN_TYPE_H
#define COMPLEX_TOKEN_TYPE_H

#include "TokenType.h"
#include "SimpleTokenType.h"
#include <vector>

class ComplexTokenType: public TokenType
{
private:
	int index = 0;	//index for type's vector
	std::vector<TokenType*> types;
public:
	ComplexTokenType();
	Scan::Type getNext(TokenType*);

	bool isAnyTokenLeft();
	void add(TokenType*);
	TokenType* next();

	void write(int x);
};

#endif 