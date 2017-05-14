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
Scan::Type ComplexTokenType::getNext()
{
	if (types.empty())
	{
		return Scan::Type::ComplexEmpty;
	}	
	while (index != types.size())
	{
		if (types[index]->isAnyTokenLeft())
		{
			Scan::Type tmp = types[index]->getNext();
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
void ComplexTokenType::add(TokenType* tokenType)
{
	types.push_back(tokenType);
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