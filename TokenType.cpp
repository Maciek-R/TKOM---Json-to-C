#include "TokenType.h"


TokenType::TokenType()
{
	anyTokenLeft = true;
}
bool TokenType::isSimpleToken()
{
	return simpleToken;
}
bool TokenType::add(TokenType *)
{
	return true;
}
bool TokenType::down()
{
	return true;
}
TokenType* TokenType::next()
{
	return NULL;
}
bool TokenType::isAnyTokenLeft()
{
	return true;
}