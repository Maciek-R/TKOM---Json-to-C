#include "Parser.h"

void Parser::serveVar()
{
/*	if (expected == Expected::Type)
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
	else if (expected == Expected::Data)
	{
		if (objectManager.isSimpleType())
		{
			objectManager.setVariableData(spell);
			exps.push_back(Scan::EndObject);

			vartype = VARTYPE::None;
		}
		else
		{	
			
		}
	}*/
}