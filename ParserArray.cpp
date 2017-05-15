#include "Parser.h"

void Parser::acceptNewSimpleArray()
{
	bool f = true;
	bool firstTime = true;
	nexts();
	while (f) {
		if (sym == Scan::EndArray) // oznacza koniec deklarowania nowych elementów tablicy
		{
			f = false;
		}
		else if (sym == Scan::Comma)
		{
			acceptNext(Scan::Object);
			acceptNewElementOfSimpleArray();
			acceptNext(Scan::EndObject);
		}
		else if (sym == Scan::Object)//nowy element tablicy
		{
			if (firstTime)
			{
				acceptNewElementOfSimpleArray();
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

void Parser::acceptNewElementOfSimpleArray()
{
	acceptNext(Scan::String);
	acceptNext(Scan::Value);
	acceptNext(Scan::String);		objectManager.addArrayValue(scan->getSpell());
}