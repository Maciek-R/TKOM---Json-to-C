#include "Parser.h"

Parser::Parser(Scan * scan)
{
	this->scan = scan;

	//exps.push_back(Scan::Object);
}

void Parser::start()
{

	acceptNext(Scan::Object);
	acceptModule();
	acceptNext(Scan::EndObject);
	
	std::cout << "Parsowanie zakonczone" << std::endl;

	

	//while (sym != Scan::Type::Error) {

		/*switch (sym) {
			case Scan::Type::Object:		setSpaces();	++tab;			cout << "Object" << endl;		break;
			case Scan::Type::Array:		setSpaces();	++tab;			cout << "Array" << endl;		break;
			case Scan::Type::Value:		setSpaces();					cout << "Value" << endl;		break;
			case Scan::Type::String:		setSpaces();					cout << "String" << " " << spell << endl;		break;
			case Scan::Type::Number:		setSpaces();					cout << "Number " << " " << spell << endl;		break;
			case Scan::Type::Comma:		setSpaces();					cout << "Comma" << endl;		break;
			case Scan::Type::Error:		setSpaces();					cout << "Error" << endl;		break;
			case Scan::Type::EndObject:	--tab;			setSpaces();	cout << "EndObject" << endl;	break;
			case Scan::Type::EndArray:	--tab;			setSpaces();	cout << "EndArray" << endl;		break;
		}*/
	//	nexts();
//	}
	objectManager.writeAll();

	//tree.write();
}

void Parser::nexts()
{
	sym = scan->nextSymbol();
}

void Parser::setSpaces()
{
	for (int i = 0; i < tab; ++i) {
		cout << '\t';
	}
}
void Parser::error(Scan::Type expected, Scan::Type typed)
{
	cout << "Unexpected token(";
	write(typed);
	cout << ").";
	cout << "Expected: ";
	write(expected);
	cout << " Line: " << scan->getLine() << endl;
	_getch();
	exit(0);
}
void Parser::write(Scan::Type tmp)
{
	switch (tmp)
	{
		case Scan::Object:			cout << "{" ; break;
		case Scan::Array:			cout << "[" ; break;
		case Scan::Value:			cout << ":" ; break;
		case Scan::String:			cout << "String"; break;
		case Scan::Number:			cout << "Number" ; break;
		case Scan::Comma:			cout << "," ; break;
		case Scan::EndObject:		cout << "}" ; break;
		case Scan::EndArray:		cout << "]" ; break;
		case Scan::Error:			cout << "error" ; break;
		case Scan::ComplexEmpty:	cout << "ComplexEmpty" ; break;
		case Scan::None:			cout << "None"; break;
		case Scan::END_FILE:		cout << "End_File"; break;
		default:					cout << "abc";
	}
}

void Parser::accept(Scan::Type type)
{
	if (sym != type)
	{
		error(type, sym);
		_getch();
		exit(0);
	}
}
void Parser::acceptNext(Scan::Type type)
{
	nexts();
	accept(type);
}
void Parser::acceptNext(Scan::Type type, char * str)
{
	acceptNext(type);
	spell = scan->getSpell();
	if (strcmp(spell, str) != 0)
	{
		cout << "Unexpected Word(" << spell << "). Expected: " << str << endl;
		_getch();
		exit(0);
	}
		
}
void Parser::acceptModule()
{
	acceptNext(Scan::String, "modulename");	
	acceptNext(Scan::Value);
	acceptNext(Scan::String);
	acceptNext(Scan::Comma);
	acceptNext(Scan::String, "module");
	acceptNext(Scan::Value);
	acceptNext(Scan::Array);

	acceptNewObject();

	accept(Scan::EndArray);
}
void Parser::acceptNewObject()
{
	bool f = true;
	bool firstTime = true;
	nexts();
	while(f)
	{
		if (sym == Scan::EndArray) // oznacza koniec deklarowania nowych obiektów
		{
			f = false;
		}
		else if (sym == Scan::Comma)//nowy obiekt - zmienna, tablica lub struktura
		{
			acceptNext(Scan::Object);
			acceptNewObjectType();
			acceptNext(Scan::EndObject);
		}
		else if (sym == Scan::Object)//nowy obiekt - zmienna, tablica lub struktura
		{
			if(firstTime)
			{
				acceptNewObjectType();
				acceptNext(Scan::EndObject);
				firstTime = false;
			}
			else 
			{
				error(Scan::Comma, Scan::Object);
			}
		}
		else {
			std::cout << "Expected { lub ]" << std::endl;
			_getch();
			exit(0);
		}
		if (f)
			nexts();
	}

}
void Parser::acceptNewObjectType()
{
	acceptNext(Scan::String);
	spell = scan->getSpell();
	if (strcmp(spell, "sequenceName") == 0)
	{
		objectManager.addStructDeclaration();
		acceptNext(Scan::Value);	
		acceptNext(Scan::String);			objectManager.setStructTypeName(scan->getSpell());
		acceptNext(Scan::Comma);
		acceptNext(Scan::String, "fields");
		acceptNext(Scan::Value);
		acceptNext(Scan::Array);

		acceptNewStructure();

		accept(Scan::EndArray);
	}
	else if (strcmp(spell, "array") == 0) 
	{
		objectManager.addArray();
		acceptNext(Scan::Value);
		acceptNext(Scan::String);			objectManager.setType(scan->getSpell());
		acceptNext(Scan::Comma);
		acceptNext(Scan::String, "name");	
		acceptNext(Scan::Value);
		acceptNext(Scan::String);			objectManager.setName(scan->getSpell());
		acceptNext(Scan::Comma);
		acceptNext(Scan::String, "values");
		acceptNext(Scan::Value);
		acceptNext(Scan::Array);

		//TODO na razie tylko typy proste
		//if(isSimple ...
		acceptNewSimpleArray();
		//else
		//acceptNewComplexArray();

		accept(Scan::EndArray);
	}
	else if (strcmp(spell, "variable") == 0) 
	{
		objectManager.addVariable();
		acceptNext(Scan::Value);
		acceptNext(Scan::String);		objectManager.setType(scan->getSpell());
		acceptNext(Scan::Comma);
		acceptNext(Scan::String, "name");
		acceptNext(Scan::Value);
		acceptNext(Scan::String);		objectManager.setName(scan->getSpell());
		acceptNext(Scan::Comma);
		acceptNext(Scan::String, "data");
		acceptNext(Scan::Value);

		//na razie typ prosty tylko
		//if(simple....
		acceptNext(Scan::String);		objectManager.setVariableData(scan->getSpell());
		//
		//else
		

	}
	else {
		std::cout << "Niepoprawny typ. Oczekiwano sequenceName, array lub variable" << std::endl;
		_getch();
		exit(0);
	}
}

