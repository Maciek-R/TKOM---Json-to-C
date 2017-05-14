#include "TokenType.h"


TokenType::TokenType()
{
	anyTokenLeft = true;
}
bool TokenType::isSimpleToken()
{
	return simpleToken;
}
void TokenType::add(TokenType *)
{

}
TokenType* TokenType::next()
{
	return NULL;
}
bool TokenType::isAnyTokenLeft()
{
	return true;
}