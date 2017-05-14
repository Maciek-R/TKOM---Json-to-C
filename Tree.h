#ifndef TREE_H
#define TREE_H

#include <vector>
#include "TokenType.h"
#include "ComplexTokenType.h"
#include "SimpleTokenType.h"

class Tree
{
private:
	int index = 0;	//index for type's vector
	std::vector<TokenType*> tokens;
	bool anyTokenLeft = true;

	TokenType * getCurrentComplexTokenType();
public:
	Tree();
	Scan::Type getNext();
	bool isAnyTokenLeft();
	void add(TokenType *);
};

#endif // !TREE_H
