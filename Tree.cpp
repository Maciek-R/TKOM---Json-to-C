#include "Tree.h"

Tree::Tree()
{
}

Scan::Type Tree::getNext()
{
	current = NULL;
	while (index != tokens.size())
	{
		if (tokens[index]->isAnyTokenLeft())
		{
			Scan::Type tmp = tokens[index]->getNext(current);
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
	while (index < tokens.size())
	{
		if (!tokens[index]->isSimpleToken())
		{
			if (tokens[index]->add(tokenType))
				return;
		}
		++index;
	}
	tokens.push_back(tokenType);
}
void Tree::down()
{
	int x = hasAnyComplexType();
	if (x != -1)
	{
		if (tokens[x]->down())
		{
			++index;
			tokens.push_back(new SimpleTokenType(Scan::EndObject));
			return;
		}
		else {
			return;
		}
	}
	else {
		return;
	}
}
int Tree::hasAnyComplexType()
{
	for (int i = index; i < tokens.size(); ++i)
	{
		if (!tokens[i]->isSimpleToken())
			return i;
	}
	return -1;
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

void Tree::write()
{
	cout << "TREE" << endl;

	for (unsigned i = 0; i < tokens.size(); ++i)
	{
		tokens[i]->write(0);
	}
}