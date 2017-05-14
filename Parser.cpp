#include "Parser.h"

Parser::Parser(Scan * scan)
{
	this->scan = scan;

	//exps.push_back(Scan::Object);
}

void Parser::start()
{
	nexts();
	while (sym != Scan::Type::Error) {

		switch (sym) {
		case Scan::Type::Object:		setSpaces();	++tab;			cout << "Object" << endl;		break;
		case Scan::Type::Array:		setSpaces();	++tab;			cout << "Array" << endl;		break;
		case Scan::Type::Value:		setSpaces();					cout << "Value" << endl;		break;
		case Scan::Type::String:		setSpaces();					cout << "String" << " " << spell << endl;		break;
		case Scan::Type::Number:		setSpaces();					cout << "Number " << " " << spell << endl;		break;
		case Scan::Type::Comma:		setSpaces();					cout << "Comma" << endl;		break;
		case Scan::Type::Error:		setSpaces();					cout << "Error" << endl;		break;
		case Scan::Type::EndObject:	--tab;			setSpaces();	cout << "EndObject" << endl;	break;
		case Scan::Type::EndArray:	--tab;			setSpaces();	cout << "EndArray" << endl;		break;
		}
		nexts();
	}

	objectManager.writeAll();
}

void Parser::nexts()
{
	
	while (tree.isAnyTokenLeft())
	{
		sym = scan->nextSymbol();
		if (sym == Scan::Error)
		{
			cout << "Generacja kodu przebiegla pomyslnie!" << endl << endl;
			_getch();
			return;
			//exit(0);
		}
		Scan::Type tmp = tree.getNext();
		write(tmp);
		cout << endl;

		if (vartype == VARTYPE::None)
		{
			if (tmp == Scan::Type::ComplexEmpty)
			{
				serveNewType();
			}
			else if(tmp != sym)
			{
				error(tmp, sym);
				_getch();
				exit(0);
			}
		}
		else if (vartype == VARTYPE::Struct)
		{
			if (expected == Expected::NextField)
			{
				if (sym == Scan::Comma)
				{
					sym = scan->nextSymbol();
					expected = Expected::Fields;
					serveStruct();
				}
				
			}

			else if (sym != Scan::String)
			{
				if (tmp != Scan::ComplexEmpty)
				{
					if (sym != tmp)
					{
						error(tmp, sym);
						_getch();
						exit(0);
					}
				}
				else 
				{
					serveStruct();
				}
				
			}
			else {
				serveStruct();
			}
		}
		else if (vartype == VARTYPE::Var)
		{

		}



		/*if (tmp == Scan::Type::ComplexEmpty && vartype != VARTYPE::None)
		{
			break;
		}
		else if (tmp == Scan::Type::ComplexEmpty)	//oznacza, ¿e potrzebuje info jakiego typu bedzie to obiekt(sequenceName, array, variable)
		{
				serveNewType();	
			sym = scan->nextSymbol();
		}
		else if (tmp != sym)
		{
			error(tmp, sym);
			_getch();
			exit(0);
		}
		else
		{
			if (tmp == Scan::Type::String)	//przepuszcza Stringi w celu ich analizy
				break;

			//sym = scan->nextSymbol();
		}*/
	}
	
	//if (vartype == VARTYPE::None)
	//	serveNewType();
	/*if (vartype == VARTYPE::Array)
		serveArray();
	else if (vartype == VARTYPE::Struct)
		serveStruct();
	else if (vartype == VARTYPE::Var)
		serveVar();*/
}



void Parser::serveNewType()
{
	//if (sym == Scan::Type::ComplexEmpty)
	//{

		spell = scan->getSpell();
		/*if (strcmp(spell, "array") == 0) {
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

		}*/
		if (strcmp(spell, "sequenceName") == 0) {
			objectManager.addStructDeclaration();
			vartype = VARTYPE::Struct;
			expected = Expected::Type;
			
			tree.add(new SimpleTokenType(Scan::Type::Value));
			tree.add(new SimpleTokenType(Scan::Type::String));
			tree.add(new SimpleTokenType(Scan::Type::Comma));
			tree.add(new SimpleTokenType(Scan::Type::String)); expsString.push_back("fields");
			tree.add(new SimpleTokenType(Scan::Type::Value));
			tree.add(new SimpleTokenType(Scan::Type::Array));
			tree.add(new ComplexTokenType());
			tree.add(new SimpleTokenType(Scan::Type::EndArray));
		/*	exps.push_back(Scan::Value);
			exps.push_back(Scan::String);
			exps.push_back(Scan::Comma);
			exps.push_back(Scan::String); expsString.push_back("fields");
			exps.push_back(Scan::Value);
			exps.push_back(Scan::Array);*/
		}
		else if (strcmp(spell, "variable") == 0) {
		/*	objectManager.addVariable();
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
			exps.push_back(Scan::Value);*/
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
		

	/*}
	else if (sym == Scan::Type::EndArray)
	{
		expected = Expected::None;
	}*/

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
void Parser::error(Scan::Type expected, Scan::Type typed)
{
	cout << "Unexpected token(";
	write(typed);
	cout << ").";
	cout << "Expected: ";
	write(expected);
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
	}
}