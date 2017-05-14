#include "SimpleTokenType.h"

SimpleTokenType::SimpleTokenType(Scan::Type type)
{
	this->type = type;
	this->simpleToken = true;
}
Scan::Type SimpleTokenType::getNext(TokenType* c)
{
	anyTokenLeft = false;
	return type;
}
bool SimpleTokenType::isAnyTokenLeft()
{
	return anyTokenLeft;
}
void SimpleTokenType::write(int x)
{
	for (int i = 0; i < x; ++i)
		cout << "    ";
	switch (type)
	{
	case Scan::Object:			cout << "{"; break;
	case Scan::Array:			cout << "["; break;
	case Scan::Value:			cout << ":"; break;
	case Scan::String:			cout << "String"; break;
	case Scan::Number:			cout << "Number"; break;
	case Scan::Comma:			cout << ","; break;
	case Scan::EndObject:		cout << "}"; break;
	case Scan::EndArray:		cout << "]"; break;
	case Scan::Error:			cout << "error"; break;
	case Scan::ComplexEmpty:	cout << "ComplexEmpty"; break;
	case Scan::None:			cout << "None"; break;
	case Scan::END_FILE:		cout << "End_File"; break;
	default:					cout << "abc";
	}
	cout << endl;
}