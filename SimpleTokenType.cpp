#include "SimpleTokenType.h"

SimpleTokenType::SimpleTokenType(Scan::Type type)
{
	this->type = type;
	this->simpleToken = true;
}
Scan::Type SimpleTokenType::getNext()
{
	anyTokenLeft = false;
	return type;
}
bool SimpleTokenType::isAnyTokenLeft()
{
	return anyTokenLeft;
}