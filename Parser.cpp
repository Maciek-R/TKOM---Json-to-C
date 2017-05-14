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
		nexts();
	}
	//objectManager.writeAll();

	tree.write();
}

void Parser::nexts()
{
	sym = scan->nextSymbol();
	if (sym == Scan::Type::Object)
	{
		tree.add(new SimpleTokenType(Scan::Type::Object));
		tree.add(new ComplexTokenType());
		
	}
	else if (sym == Scan::Type::EndObject)
		tree.down();
	else {
		tree.add(new SimpleTokenType(sym));
	}
	


	//if (sym == Scan::Object)
	//{

	//}

	/*while (tree.isAnyTokenLeft())
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
		//write(tmp);
		//cout << endl;

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
				else if (sym == Scan::Object)
				{
					cout << "Expected ','" << endl;
					_getch();
					exit(0);
				}
				else if (sym == Scan::EndArray)
				{
					sym = scan->nextSymbol();
					vartype = VARTYPE::None;
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
			if (expected == Expected::NextDataValue && !objectManager.isSimpleType())
			{
				if (sym == Scan::Comma)
				{
					sym = scan->nextSymbol();
					expected = Expected::Data;
					serveArray();
				}
				else if (sym == Scan::Object)
				{
					cout << "Expected ','" << endl;
					_getch();
					exit(0);
				}
				else if (sym == Scan::EndArray)
				{
					sym = scan->nextSymbol();
					vartype = VARTYPE::None;
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
					serveVar();
				}
			}
			else {
				serveVar();
			}
		}
		else if (vartype == VARTYPE::Array)
		{
			if (expected == Expected::NextDataValue)
			{
				if (sym == Scan::Comma)
				{
					sym = scan->nextSymbol();
					expected = Expected::Values;
					serveArray();
				}
				else if (sym == Scan::Object)
				{
					cout << "Expected ','" << endl;
					_getch();
					exit(0);
				}
				else if (sym == Scan::EndArray)
				{
					sym = scan->nextSymbol();
					vartype = VARTYPE::None;
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
					serveArray();
				}
			}
			else {
				serveArray();
			}
		}

		
	}*/
}



void Parser::serveNewType()
{
	if (sym == Scan::Object)
	{
		tree.add(new ComplexTokenType());
	

		sym = scan->nextSymbol();
		spell = scan->getSpell();

		if (strcmp(spell, "sequenceName") == 0) {
			cout << "seq" << endl;
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
		}
		else if (strcmp(spell, "variable") == 0) {
			objectManager.addVariable();
			cout << "asdasdasjdhahfdaskhdjkashdnsaljfnsdfsdfsdnfksdnfkndskfndskkd" << endl;
			vartype = VARTYPE::Var;
			expected = Expected::Type;

			tree.add(new SimpleTokenType(Scan::Value));
			tree.add(new SimpleTokenType(Scan::String));
			tree.add(new SimpleTokenType(Scan::Comma));
			tree.add(new SimpleTokenType(Scan::String)); expsString.push_back("name");
			tree.add(new SimpleTokenType(Scan::Value));
			tree.add(new SimpleTokenType(Scan::String));
			tree.add(new SimpleTokenType(Scan::Comma));
			tree.add(new SimpleTokenType(Scan::String)); expsString.push_back("data");
			tree.add(new SimpleTokenType(Scan::Value));
			//tree.add(new SimpleTokenType(Scan::String));
			tree.add(new ComplexTokenType());
		}
		else if (strcmp(spell, "array") == 0) {
			objectManager.addArray();
			vartype = VARTYPE::Array;
			expected = Expected::Type;

			tree.add(new SimpleTokenType(Scan::Value));
			tree.add(new SimpleTokenType(Scan::String));
			tree.add(new SimpleTokenType(Scan::Comma));
			tree.add(new SimpleTokenType(Scan::String)); expsString.push_back("name");
			tree.add(new SimpleTokenType(Scan::Value));
			tree.add(new SimpleTokenType(Scan::String));
			tree.add(new SimpleTokenType(Scan::Comma));
			tree.add(new SimpleTokenType(Scan::String)); expsString.push_back("values");
			tree.add(new SimpleTokenType(Scan::Value));
			tree.add(new SimpleTokenType(Scan::Array));
			tree.add(new ComplexTokenType());
			tree.add(new SimpleTokenType(Scan::Type::EndArray));
		}
		else {
			cout << "Unexpected word. Expected: sequenceName, array, variable" << endl;
			_getch();
			exit(0);
		}
	}
	else if (sym == Scan::EndArray)
	{

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
		case Scan::None:			cout << "None"; break;
		case Scan::END_FILE:		cout << "End_File"; break;
		default:					cout << "abc";
	}
}