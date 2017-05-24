#include "Parser.h"

void Parser::acceptNewVariable(std::string typeName)
{
	Model* m = objectManager.getStructureWithTypeName(typeName);
	int size = m->getFieldsAndTypesSize();
	int i = 0;

	bool f = true;
	bool firstTime = true;
	nexts();
	while (f) {

		

		if (sym == Scan::EndArray) // oznacza koniec 
		{
			f = false;
		}
		else if (sym == Scan::Comma)//kolejny element zmiennej strukturalnej
		{
			acceptNext(Scan::Object);
			if (i == size)
			{
				std::cout << "Too many variables! Should be "<<size<< " .Line: " << scan->getLine() << std::endl;
				_getch();
				exit(0);
			}
			acceptNewElementOfVariable(m->getFieldName(i), true);
			++i;
			acceptNext(Scan::EndObject);
		}
		else if (sym == Scan::Object)//pierwszy element zmiennej strukturalnej
		{
			if (firstTime)
			{
				acceptNewElementOfVariable(m->getFieldName(i), true);
				++i;
				acceptNext(Scan::EndObject);
				firstTime = false;
			}
			else {
				error(Scan::Comma, Scan::Object);
			}

		}
		else {
			std::cout << "Expected { or ] or ,. Line: "<<scan->getLine() << std::endl;
			_getch();
			exit(0);
		}
		if (f)
			nexts();
	}
}

void Parser::acceptNewElementOfVariable(std::string name, bool isSimpleType)
{
	acceptNext(Scan::String, "attrib");
	acceptNext(Scan::Value); 
	acceptNext(Scan::String, name.c_str());	objectManager.setStructFieldType(scan->getSpell());
	acceptNext(Scan::Comma);
	acceptNext(Scan::String, "value");
	acceptNext(Scan::Value);
	
	acceptNext(Scan::String);				objectManager.setStructFieldName(scan->getSpell());
	
	
}
