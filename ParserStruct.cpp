#include "Parser.h"

void Parser::acceptNewStructure()
{
	bool f = true;
	bool firstTime = true;
	nexts();
	while (f) {
		if (sym == Scan::EndArray) // oznacza koniec deklarowania nowychelementów struktury
		{
			f = false;
		}
		else if (sym == Scan::Comma)
		{
			acceptNext(Scan::Object);
			acceptNewElementOfStructure();
			acceptNext(Scan::EndObject);
		}
		else if (sym == Scan::Object)//nowy element struktury
		{
			if (firstTime)
			{
				acceptNewElementOfStructure();
				acceptNext(Scan::EndObject);
				firstTime = false;
			}
			else {
				error(Scan::Comma, Scan::Object);
			}

		}
		else {
			std::cout << "Expected { or ] or ," << std::endl;
			_getch();
			exit(0);
		}
		if (f)
			nexts();
	}
}

void Parser::acceptNewElementOfStructure()
{
	acceptNext(Scan::String, "attrib");
	acceptNext(Scan::Value);
	acceptNext(Scan::String);	objectManager.setStructFieldName(scan->getSpell());
	acceptNext(Scan::Comma);
	acceptNext(Scan::String, "type");
	acceptNext(Scan::Value);
	acceptNext(Scan::String);	objectManager.setStructFieldType(scan->getSpell());
}