#include "Parser.h"

void Parser::serveVar()
{
	if (expected == Expected::Type)
	{
		if (objectManager.checkIfTypeIsExisting(spell))
		{
			objectManager.setType(spell);
			expected = Expected::WordName;

			if (!objectManager.isSimpleType())
			{
				tree.add(new SimpleTokenType(Scan::Type::Array));
				tree.add(new ComplexTokenType());
				tree.add(new SimpleTokenType(Scan::Type::EndArray));
			}
		}
		else
		{
			cout << "Undefined type: " << spell << endl;
			_getch();
			exit(0);
		}
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
		expected = Expected::WordData;
	}
	else if (expected == Expected::WordData)
	{
		if (expsString[0] != spell)
		{
			cout << "Unexpected word. Expected: \"data\"" << endl;
			_getch();
			exit(0);
		}
		else
		{
			expsString.erase(expsString.begin());
		}
		expected = Expected::Data;			//oczekuje siê { - pierwsza zmienna w strukturze
											// lub ] - wtedy jest pusta struktura(nie ma w niej zmiennych
											// lub , - kolejna zmienna w strukturze(nie pierwsza)
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
		expected = Expected::Name;		
	}
	else if (expected == Expected::Name)
	{
		//tu powinno byc sprawdzenie czy jest dobra nazwa
		expected = Expected::WordValue;
	}
	else if (expected == Expected::WordValue)
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
			objectManager.setVariableData(spell);
			expected = Expected::NextDataValue;
	}
	else if (expected == Expected::Data)
	{
		if (objectManager.isSimpleType())
		{
			objectManager.setVariableData(spell);
			vartype = VARTYPE::None;
		}
		else
		{	
			if (sym == Scan::Object)	
			{
				tree.add(new SimpleTokenType(Scan::String));  expsString.push_back("attrib");
				tree.add(new SimpleTokenType(Scan::Value));
				tree.add(new SimpleTokenType(Scan::String));
				tree.add(new SimpleTokenType(Scan::Comma));
				tree.add(new SimpleTokenType(Scan::String));  expsString.push_back("value");
				tree.add(new SimpleTokenType(Scan::Value));
				tree.add(new SimpleTokenType(Scan::String));
				tree.add(new SimpleTokenType(Scan::EndObject));

				tree.add(new ComplexTokenType());		// to jest wa¿ne, definiujemy ze coœ mo¿e tu byæ, ale nie musi
				expected = Expected::WordAttrib;

			}
			else if (sym == Scan::EndArray)
			{
				cout << "KONIEC" << endl;
				vartype = VARTYPE::None;
			}
			else
			{
				cout << "Unexpected token("; write(sym); cout << "). Expected: '{', ',', or ']' " << endl;
				_getch();
				exit(0);
			}
		}
	}
}