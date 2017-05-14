#include "Tree.h"

Tree::Tree()
{
	tokens.push_back(new SimpleTokenType(Scan::Object));
	tokens.push_back(new SimpleTokenType(Scan::String));
	tokens.push_back(new SimpleTokenType(Scan::Value));
	tokens.push_back(new SimpleTokenType(Scan::String));
	tokens.push_back(new SimpleTokenType(Scan::Comma));
	tokens.push_back(new SimpleTokenType(Scan::String));
	tokens.push_back(new SimpleTokenType(Scan::Value));
	tokens.push_back(new SimpleTokenType(Scan::Array));
	tokens.push_back(new ComplexTokenType());


	tokens.push_back(new SimpleTokenType(Scan::EndArray));
	tokens.push_back(new SimpleTokenType(Scan::EndObject));
}

Scan::Type Tree::getNext()
{
	while (index != tokens.size())
	{
		if (tokens[index]->isAnyTokenLeft())
		{
			Scan::Type tmp = tokens[index]->getNext();
			if (tmp != Scan::Type::None)
				return tmp;
		}

		++index;
	}
	anyTokenLeft = false;

	return Scan::Type::None;
}

bool Tree::isAnyTokenLeft()
{
	return anyTokenLeft;
}
void Tree::add(TokenType * tokenType)
{
	TokenType * current = getCurrentComplexTokenType();
	
	current->add(tokenType);
}

TokenType* Tree::getCurrentComplexTokenType()
{
	for (unsigned i = index; i < tokens.size(); ++i)
	{
		if (!tokens[i]->isSimpleToken())	// tu trzeba bedzie poprawic to zeby szukalo pierwszego juz obslugiwanego a nie pierwszego znalezionego
			if(tokens[i]->isAnyTokenLeft())
				if (tokens[i]->next() != NULL) {
					return tokens[i]->next();
				}
	}
	return NULL;
}