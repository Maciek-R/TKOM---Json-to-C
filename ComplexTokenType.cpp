#include "ComplexTokenType.h"

ComplexTokenType::ComplexTokenType()
{
	/*if (type == "fields")
	{
		types.push_back(new SimpleTokenType(Scan::Type::Object));
		types.push_back(new SimpleTokenType(Scan::Type::String));
		types.push_back(new SimpleTokenType(Scan::Type::Value));
		types.push_back(new SimpleTokenType(Scan::Type::String));
		types.push_back(new SimpleTokenType(Scan::Type::Comma));
		types.push_back(new SimpleTokenType(Scan::Type::String));
		types.push_back(new SimpleTokenType(Scan::Type::Value));
		types.push_back(new SimpleTokenType(Scan::Type::String));
		types.push_back(new SimpleTokenType(Scan::Type::EndObject));
	}*/
}
Scan::Type ComplexTokenType::getNext(TokenType* current)
{
	current = this;
	if (types.empty())
	{
		current = this;
		return Scan::Type::ComplexEmpty;
	}	
	while (index != types.size())
	{
		if (types[index]->isAnyTokenLeft())
		{
			Scan::Type tmp = types[index]->getNext(current);
			if (tmp != Scan::Type::None)
				return tmp;
		}

		++index;
	}
	anyTokenLeft = false;

	return Scan::Type::None;
}

bool ComplexTokenType::isAnyTokenLeft()
{
	return anyTokenLeft;
}
bool ComplexTokenType::add(TokenType* tokenType)
{
	while (index < types.size())
	{
		if (!types[index]->isSimpleToken())
		{
			if (types[index]->add(tokenType))
				return true;
		}
		++index;
	}
	types.push_back(tokenType);
	return true;
}
bool ComplexTokenType::down()
{
	int x = hasAnyComplexType();
	if (x != -1)
	{
		if (types[x]->down())
		{
			++index;
			types.push_back(new SimpleTokenType(Scan::EndObject));
			return false;
		}
		else {
			return false;
		}
	}
	else {
		return true;
	}
}
int ComplexTokenType::hasAnyComplexType()
{
	for (int i = index; i < types.size(); ++i)
	{
		if (!types[i]->isSimpleToken())
			return i;
	}
	return -1;
}
TokenType* ComplexTokenType::next()
{
	if (types.empty())
		return this;

	if (types[index]->isSimpleToken())
		return this;

	for (unsigned i = index; i < types.size(); ++i)
	{
		if (!types[i]->isSimpleToken())
		{
			if (types[i]->isAnyTokenLeft())
				if (types[i]->next() != NULL)
					return types[i]->next();
		}
	}
	return NULL;
}
void ComplexTokenType::write(int x)
{
	

	//cout << "ComplexTokenType" << endl;

	for (unsigned i = 0; i < types.size(); ++i)
	{
		types[i]->write(x+1);
	}
}