#include "Parser.h"

Parser::Parser(Scan * scan)
{
	this->scan = scan;

	exps.push_back(Scan::Object);
}

void Parser::start()
{
	nexts();
	while (sym != Scan::Error) {

		switch (sym) {
		case Scan::Object:		setSpaces();	++tab;			cout << "Object" << endl;		break;
		case Scan::Array:		setSpaces();	++tab;			cout << "Array" << endl;		break;
		case Scan::Value:		setSpaces();					cout << "Value" << endl;		break;
		case Scan::String:		setSpaces();					cout << "String" << " " << spell << endl;		break;
		case Scan::Number:		setSpaces();					cout << "Number " << " " << spell << endl;		break;
		case Scan::Comma:		setSpaces();					cout << "Comma" << endl;		break;
		case Scan::Error:		setSpaces();					cout << "Error" << endl;		break;
		case Scan::EndObject:	--tab;			setSpaces();	cout << "EndObject" << endl;	break;
		case Scan::EndArray:	--tab;			setSpaces();	cout << "EndArray" << endl;		break;
		}
		nexts();
	}

	objectManager.writeAll();
}

void Parser::nexts()
{
	sym = scan->nextSymbol();

	while (!exps.empty())
	{
		if (exps[0] != sym) {
			cout << "Unexpected token. Expected: " << exps[0] << endl;
			_getch();
			exit(0);
		}
		else
		{
			Scan::Type tmp = exps[0];
			exps.erase(exps.begin());	//zawiera kolejke tokenów, które powinny pojawiaæ siê w odpowiedniej kolejnoœci
			if (tmp == Scan::String)	//przepuszcza Stringi w celu ich analizy
				break;

			sym = scan->nextSymbol();
		}
	}

	if (vartype == VARTYPE::None)
		serveNewType();
	else if (vartype == VARTYPE::Array)
		serveArray();
	else if (vartype == VARTYPE::Struct)
		serveStruct();
	else if (vartype == VARTYPE::Var)
		serveVar();
}



void Parser::serveNewType()
{
	if (sym == Scan::Type::String)
	{
		spell = scan->getSpell();

		if (strcmp(spell, "array") == 0) {
			objectManager.addArray();
			vartype = VARTYPE::Array;
			expected = Expected::Type;

			exps.push_back(Scan::Value);
			exps.push_back(Scan::String);
			exps.push_back(Scan::Comma);
			exps.push_back(Scan::String); expsString.push_back("name");
			exps.push_back(Scan::Value);
			exps.push_back(Scan::String);
			exps.push_back(Scan::Comma);
			exps.push_back(Scan::String); expsString.push_back("values");
			exps.push_back(Scan::Value);
			exps.push_back(Scan::Array);

			exps.push_back(Scan::Object);
			exps.push_back(Scan::String);  expsString.push_back("value");
			exps.push_back(Scan::Value);
			exps.push_back(Scan::String);
			exps.push_back(Scan::EndObject);

		}
		else if (strcmp(spell, "sequenceName") == 0) {
			objectManager.addStructDeclaration();
			vartype = VARTYPE::Struct;
			expected = Expected::Type;

			exps.push_back(Scan::Value);
			exps.push_back(Scan::String);
			exps.push_back(Scan::Comma);
			exps.push_back(Scan::String); expsString.push_back("fields");
			exps.push_back(Scan::Value);
			exps.push_back(Scan::Array);
		}
		else if (strcmp(spell, "variable") == 0) {
			objectManager.addVariable();
			vartype = VARTYPE::Var;
			expected = Expected::Type;

			exps.push_back(Scan::Value);
			exps.push_back(Scan::String);
			exps.push_back(Scan::Comma);
			exps.push_back(Scan::String); expsString.push_back("name");
			exps.push_back(Scan::Value);
			exps.push_back(Scan::String);
			exps.push_back(Scan::Comma);
			exps.push_back(Scan::String); expsString.push_back("data");
			exps.push_back(Scan::Value);
		}
		else {
			cout << "Unexpected word. Expected: sequenceName, array, " << endl;
			_getch();
			exit(0);
		}

		/*else if (strcmp(spell, "SequenceName") == 0) {
			objectManager.addStructDeclaration();
			expected = Expected::StructTypeName;
		}
		else if (strcmp(spell, "fields") == 0) {
			expected = Expected::Fields;
		}
		else if (strcmp(spell, "variable") == 0) {
			expected = Expected::Type;
			objectManager.addVariable();
		}
		else if (strcmp(spell, "data") == 0) {
			expected = Expected::DataValue;
		}*/


		//

		//
		

	}
	else if (sym == Scan::Type::EndArray)
	{
		expected = Expected::None;
	}

}
void Parser::serveArray()
{
	if (expected == Expected::WordValues) {
		if (expsString[0] != spell)
		{
			cout << "Unexpected word. Expected: \"values\"" << endl;
			_getch();
			exit(0);
		}
		else
		{
			expsString.erase(expsString.begin());
		}
		expected = Expected::Values;
	}
	else if (expected == Expected::Type)
	{
		objectManager.setType(spell);
		expected = Expected::WordName;
	}
	else if (expected == Expected::WordName)
	{
		if (expsString[0] != spell)
		{
			cout << "Unexpected word. Expected: \"name\"" << endl;
			_getch();
			exit(0);
		}
		else
		{
			expsString.erase(expsString.begin());
		}

		expected = Expected::Name;
	}
	else if (expected == Expected::Name)
	{
		objectManager.setName(spell);
		expected = Expected::WordValues;
	}
	else if (expected == Expected::StructTypeName)
	{
		objectManager.setStructTypeName(spell);
		expected = Expected::None;
	}
	else if (expected == Expected::Values)
	{
		if (expsString[0] != spell)
		{
			cout << "Unexpected word. Expected: \"value\"" << endl;
			_getch();
			exit(0);
		}
		else
		{
			expsString.erase(expsString.begin());
		}

		expected = Expected::Value;
	}
	else if (expected == Expected::Value)
	{
		objectManager.addArrayValue(spell);
		expected = Expected::Values;
	}
	else if (expected == Expected::Fields)
	{
		if (strcmp(spell, "attrib") == 0)
		{
			expected = Expected::FieldName;
		}
		else
		{
			//tu sygnalizacja bledu, bo powinno byc "attrib"
		}
	}
	else if (expected == Expected::FieldName)
	{
		objectManager.setStructFieldName(spell);
		expected = Expected::FieldType;
	}
	else if (expected == Expected::FieldType)
	{
		if (strcmp(spell, "type") == 0)
		{
			expected = Expected::FieldTypeName;
		}
		else
		{
			//tu sygnalizacja bledu, bo powinno byc "type"
		}
	}
	else if (expected == Expected::FieldTypeName)
	{
		objectManager.setStructFieldType(spell);
		expected = Expected::Fields;
	}
	else if (expected == Expected::DataValue)
	{
		objectManager.setVariableData(spell);
		expected = Expected::None;
	}

}

void Parser::setSpaces()
{
	for (int i = 0; i < tab; ++i) {
		cout << '\t';
	}
}