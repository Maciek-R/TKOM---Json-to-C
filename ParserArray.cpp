#include "Parser.h"

void Parser::serveArray()
{
	if (expected == Expected::Type)
	{
		if (objectManager.checkIfTypeIsExisting(spell))
		{
			objectManager.setType(spell);
			expected = Expected::WordName;
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
		expected = Expected::WordValues;
	}
	else if (expected == Expected::WordValues)
	{
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
		expected = Expected::Values;			//oczekuje siê { - pierwsza zmienna w strukturze
											// lub ] - wtedy jest pusta struktura(nie ma w niej zmiennych
											// lub , - kolejna zmienna w strukturze(nie pierwsza)
	}
	else if (expected == Expected::Values)
	{
		if (sym == Scan::Object)	//nie dodaje go do listy exps, bo juz zosta³ sprawdzony
		{
			tree.add(new SimpleTokenType(Scan::String));  expsString.push_back("value");
			tree.add(new SimpleTokenType(Scan::Value));
			tree.add(new SimpleTokenType(Scan::String));
			tree.add(new SimpleTokenType(Scan::EndObject));

			tree.add(new ComplexTokenType());		// to jest wa¿ne, definiujemy ze coœ mo¿e tu byæ, ale nie musi
			expected = Expected::WordValue;

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
		expected = Expected::DataValue;
	}

	else if (expected == Expected::DataValue)
	{
		//objectManager.setVariableData(spell);
		objectManager.addArrayValue(spell);
		expected = Expected::NextDataValue;
	}

}