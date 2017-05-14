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
	int hasAnyComplexType();
public:
	ComplexTokenType* current;	//current ComplexTokenType in tree
	Tree();
	Scan::Type getNext();
	bool isAnyTokenLeft();
	void add(TokenType *);
	void down();

	void write();
};

#endif // !TREE_H
