#include "Parser.h"

Parser::Parser(Scan * scan)
{
	this->scan = scan;
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
	if (sym == Scan::Type::String)
	{
		spell = scan->getSpell();

		if (expected == Expected::None) {
			if (strcmp(spell, "array") == 0) {
				objectManager.addArray();
				expected = Expected::Type;
			}
			else if (strcmp(spell, "name") == 0) {
				expected = Expected::Name;
			}
			else if (strcmp(spell, "values") == 0) {
				expected = Expected::Values;
			}
			else if (strcmp(spell, "SequenceName") == 0) {
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
			}
			

			//

			//
		}
		else if (expected == Expected::Type)
		{
			objectManager.setType(spell);
			expected = Expected::None;
		}
		else if (expected == Expected::Name)
		{
			objectManager.setName(spell);
			expected = Expected::None;
		}
		else if (expected == Expected::StructTypeName)
		{
			objectManager.setStructTypeName(spell);
			expected = Expected::None;
		}
		else if (expected == Expected::Values)
		{
			if (strcmp(spell, "value") == 0)
			{
				expected = Expected::Value;
			}
			else
			{
				//tu sygnalizacja bledu, bo powinno byc "value"
			}
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
	else if (sym == Scan::Type::EndArray)
	{
		expected = Expected::None;
	}
	
}

void Parser::setSpaces()
{
	for (int i = 0; i < tab; ++i) {
		cout << '\t';
	}
}