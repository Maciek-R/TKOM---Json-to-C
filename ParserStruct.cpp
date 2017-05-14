#include "Parser.h"

void Parser::serveStruct()
{
	if (expected == Expected::Type)
	{
		objectManager.setStructTypeName(spell);
		expected = Expected::WordFields;
	}
	else if (expected == Expected::WordFields)
	{
		if (expsString[0] != spell)
		{
			cout << "Unexpected word("<<spell<<"). Expected: \"fields\"" << endl;
			_getch();
			exit(0);
		}
		else
		{
			expsString.erase(expsString.begin());
		}

		expected = Expected::Fields;	//oczekuje siê { - pierwsza zmienna w strukturze
										// lub ] - wtedy jest pusta struktura(nie ma w niej zmiennych
										// lub , - kolejna zmienna w strukturze(nie pierwsza)
	}
	else if (expected == Expected::Fields)
	{
		if (sym == Scan::Object)	//nie dodaje go do listy exps, bo juz zosta³ sprawdzony
		{
			tree.add(new SimpleTokenType(Scan::String));  expsString.push_back("attrib"); cout << "dodano" << endl;
			tree.add(new SimpleTokenType(Scan::Value));
			tree.add(new SimpleTokenType(Scan::String));
			tree.add(new SimpleTokenType(Scan::Comma));
			tree.add(new SimpleTokenType(Scan::String));  expsString.push_back("type");
			tree.add(new SimpleTokenType(Scan::Value));
			tree.add(new SimpleTokenType(Scan::String));
			tree.add(new SimpleTokenType(Scan::EndObject));

			tree.add(new ComplexTokenType());		// to jest wa¿ne, definiujemy ze coœ mo¿e tu byæ, ale nie musi
			expected = Expected::WordAttrib;
			
		}
		else if (sym == Scan::Comma)	// to chyba do wyrzucenia
		{
			cout << "asdasdasdasdasdasdasdasd" << endl;
			tree.add(new SimpleTokenType(Scan::Object));
			tree.add(new SimpleTokenType(Scan::String));  expsString.push_back("attrib");
			tree.add(new SimpleTokenType(Scan::Value));
			tree.add(new SimpleTokenType(Scan::String));
			tree.add(new SimpleTokenType(Scan::Comma));
			tree.add(new SimpleTokenType(Scan::String)); expsString.push_back("type");
			tree.add(new SimpleTokenType(Scan::Value));
			tree.add(new SimpleTokenType(Scan::String));
			tree.add(new SimpleTokenType(Scan::EndObject));

			expected = Expected::WordAttrib;
		}
		else if (sym == Scan::EndArray)
		{
			//exps.push_back(Scan::EndObject);
			vartype = VARTYPE::None;
		}
		else
		{
			cout << "Unexpected token("; write(sym); cout <<"). Expected: '{', ',', or ']' " << endl;
			_getch();
			exit(0);
		}

	}
	else if (expected == Expected::WordAttrib)
	{
		if (expsString[0] != spell)
		{
			cout << "Unexpected word. Expected: \"attrib\"" << endl;
			_getch();
			exit(0);
		}
		else
		{
			expsString.erase(expsString.begin());
		}

		expected = Expected::FieldName;
	}
	else if (expected == Expected::FieldName)
	{
		objectManager.setStructFieldName(spell);
		expected = Expected::WordType;
	}
	else if (expected == Expected::WordType)
	{
		if (expsString[0] != spell)
		{
			cout << "Unexpected word. Expected: \"type\"" << endl;
			_getch();
			exit(0);
		}
		else
		{
			expsString.erase(expsString.begin());
		}

		expected = Expected::FieldType;
	}
	else if (expected == Expected::FieldType)
	{
		if (objectManager.checkIfTypeIsExisting(spell))
		{
			objectManager.setStructFieldType(spell);
			expected = Expected::NextField;
		}
		else 
		{
			cout << "Undefined: " << spell << endl;
			_getch();
			exit(0);
		}
	}
}