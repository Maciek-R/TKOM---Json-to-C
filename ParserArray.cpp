#include "Parser.h"
/*
void Parser::acceptNewArray(bool isSimple)
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
			if (isSimple)
				acceptNewElementOfSimpleArray();
			else
				acceptNewElementOfComplexArray();
			acceptNext(Scan::EndObject);
		}
		else if (sym == Scan::Object)//nowy element tablicy
		{
			if (firstTime)
			{
				if (isSimple)
					acceptNewElementOfSimpleArray();
				else
					acceptNewElementOfComplexArray();
				acceptNext(Scan::EndObject);
				firstTime = false;
			}
			else {
				error(Scan::Comma, Scan::Object);
			}

		}
		else {
			std::cout << "Expected { or ] or ,. Line: " <<scan->getLine()<< std::endl;
			_getch();
			exit(0);
		}
		if (f)
			nexts();
	}
}

void Parser::acceptNewElementOfSimpleArray()
{
	acceptNext(Scan::String, "value");
	acceptNext(Scan::Value);
	acceptNext(Scan::String);		objectManager.addArrayValue(scan->getSpell());
}

void Parser::acceptNewStructInArray()
{
	Model*m = new Model(Model::Var);
	m->setSimpleType(false);

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
			acceptNewElementStructInArray(m);
			acceptNext(Scan::EndObject);
		}
		else if (sym == Scan::Object)//nowy element tablicy
		{
			if (firstTime)
			{
				acceptNewElementStructInArray(m);
				acceptNext(Scan::EndObject);
				firstTime = false;

			}
			else {
				error(Scan::Comma, Scan::Object);
			}

		}
		else {
			std::cout << "Expected { or ] or ,. Line: " << scan->getLine() << std::endl;
			_getch();
			exit(0);
		}
		if (f)
			nexts();
	}

	objectManager.addModel(m);
}

void Parser::acceptNewElementOfComplexArray()
{
	acceptNext(Scan::String, "value");
	acceptNext(Scan::Value);
	acceptNext(Scan::Array);
	acceptNewStructInArray();
	accept(Scan::EndArray);
}

void Parser::acceptNewElementStructInArray(Model *m)
{
	acceptNext(Scan::String, "attrib");		
	acceptNext(Scan::Value);
	acceptNext(Scan::String);		m->setStructFieldType(scan->getSpell());//objectManager.addArrayValue(scan->getSpell());
	acceptNext(Scan::Comma);	
	acceptNext(Scan::String, "value");
	acceptNext(Scan::Value);
	acceptNext(Scan::String);		m->setStructFieldName(scan->getSpell()); 
}*/