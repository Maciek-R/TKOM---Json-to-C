#include "Parser.h"

Parser::Parser(Scan * scan)
{
	this->scan = scan;
}

void Parser::start()
{
	acceptModule();
	
	std::cout << "Parsing completed." << std::endl;
}

void Parser::writeAllToFile(std::string outputFile)
{
	objectManager.writeAll(outputFile);
}

void Parser::nexts()
{
	sym = scan->nextSymbol();
}

void Parser::printError(std::string err)
{
	std::cout << err << std::endl;
	std::cout << "Line: " << scan->getLine() << std::endl;
	_getch();
	exit(0);
}
void Parser::error(Scan::Type expected, Scan::Type typed)
{
	cout << "Unexpected token(";
	writeToken(typed);
	cout << ").";
	cout << "Expected: ";
	writeToken(expected);
	cout << " Line: " << scan->getLine() << endl;
	_getch();
	exit(0);
}
void Parser::checkTypeWithContent(std::string type, std::string data)
{
	if (type == "string") return;

	for (size_t i = 0; i < data.size(); ++i)
		if (!Source::isDigit(data[i]))
			printError("Uncorrect format of data in variable");

	if (type == "int")
	{
		if(data.find('.')!=-1)
			printError("Uncorrect format of data in variable");
	}
	else if (type == "float" || type == "double")
	{
		int f = data.find('.');
		if (f != -1 && (data.find('.', f+1))!=-1)
			printError("Uncorrect format of data in variable");

		int number;
		try
		{
			int num = std::stoi(data);
		}
		catch (exception e)
		{
			std::string error = "Uncorrect format of data in variable";
			printError(error);
		}
	}
}
void Parser::writeToken(Scan::Type tmp)
{
	switch (tmp)
	{
		case Scan::Object:			cout << "{" ; break;
		case Scan::Array:			cout << "[" ; break;
		case Scan::Value:			cout << ":" ; break;
		case Scan::String:			cout << "String"; break;
		case Scan::Comma:			cout << "," ; break;
		case Scan::EndObject:		cout << "}" ; break;
		case Scan::EndArray:		cout << "]" ; break;
		case Scan::Error:			cout << "error" ; break;
		case Scan::None:			cout << "None"; break;
		case Scan::END_FILE:		cout << "End_File"; break;
		default:					cout << "Unknown";
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
void Parser::acceptNext(Scan::Type type, const char * str)
{
	acceptNext(type);
	spell = scan->getSpell();
	if (strcmp(spell, str) != 0)
	{
		cout << "Unexpected Word(" << spell << "). Expected: " << str <<". Line: "<< scan->getLine() << endl;
		_getch();
		exit(0);
	}
		
}
void Parser::acceptModule()
{
	acceptNext(Scan::Object);

	acceptNext(Scan::String, "modulename");	
	acceptNext(Scan::Value);
	acceptNext(Scan::String);
	acceptNext(Scan::Comma);

	acceptModuleArray();

	acceptNext(Scan::EndObject);
}
void Parser::acceptModuleArray()
{
	acceptNext(Scan::String, "module");
	acceptNext(Scan::Value);
	acceptNext(Scan::Array);

	acceptNewObjects();

	accept(Scan::EndArray);
}
void Parser::acceptNewObjects()
{
	while (acceptNewObject());
}



bool Parser::acceptNewObject()
{
	acceptNext(Scan::Object);

	acceptNext(Scan::String);
	spell = scan->getSpell();

	if (strcmp(spell, "sequenceName") == 0)
	{
		acceptSequenceName();
	}
	else if (strcmp(spell, "array") == 0) 
	{
		acceptArray();
	}
	else if (strcmp(spell, "variable") == 0)
	{
		acceptVar();
	}
	else 
	{
		std::string error = "Unexpected type. Expected: sequenceName, array or variable.";
		printError(error);
	}

	accept(Scan::EndObject);
	nexts();
	return sym == Scan::Comma;
}

void Parser::acceptSequenceName()
{
	acceptNext(Scan::Value);
	acceptNext(Scan::String);

	spell = scan->getSpell();
	std::string type = spell;

	if (objectManager.existsStructureType(type)) 
	{
		std::string error = "Structure type \"" + type + "\" already defined!";
		printError(error);
	}
	Structure *structure = new Structure(type);

	acceptNext(Scan::Comma);
	acceptNext(Scan::String, "fields");
	acceptNext(Scan::Value);

	acceptSequenceFields(structure);
	
	objectManager.addStructureType(structure);

	nexts();
}

void Parser::acceptSequenceFields(Structure* structure)
{
	acceptNext(Scan::Array);
	while (acceptSequenceField(structure));
	accept(Scan::EndArray);
}
bool Parser::acceptSequenceField(Structure* structure)
{
	acceptNext(Scan::Object);

	acceptNext(Scan::String, "attrib");
	acceptNext(Scan::Value);
	acceptNext(Scan::String);

	spell = scan->getSpell();
	std::string name = spell;

	if (objectManager.existsStructField(structure, name)) 
	{
		std::string error = "Structure field with name \"" + name + "\" already exists.";
		printError(error);
	}

	acceptNext(Scan::Comma);

	acceptNext(Scan::String, "type");
	acceptNext(Scan::Value);
	acceptNext(Scan::String);

	spell = scan->getSpell();
	std::string type = spell;

	if (!objectManager.existsType(type)) {
		std::string error = "Structure field type \"" + type + "\" doesn't exists";
		printError(error);
	}
	
	objectManager.addStructureField(structure, name, type);

	acceptNext(Scan::EndObject);
	nexts();
	return sym == Scan::Comma;
}
void Parser::acceptArray() {

	acceptNext(Scan::Value);
	acceptNext(Scan::String);
	spell = scan->getSpell();

	std::string type = spell;
	if (!objectManager.existsType(type))
		printError("This type \"" + type + "\" does not exists");
	acceptNext(Scan::Comma);

	acceptNext(Scan::String, "name");
	acceptNext(Scan::Value);
	acceptNext(Scan::String);
	spell = scan->getSpell();
	std::string name = spell;
	acceptNext(Scan::Comma);

	acceptNext(Scan::String, "values");
	acceptNext(Scan::Value);

	Array* arr = objectManager.addArrayVariable(name, type);
	acceptArrayElements(arr);

	nexts();
}
void Parser::acceptArrayElements(Array* arr)
{
	acceptNext(Scan::Array);
	while (acceptArrayElement(arr));
	accept(Scan::EndArray);
}

bool Parser::acceptArrayElement(Array* arr)
{
	acceptNext(Scan::Object);

	acceptNext(Scan::String, "value");
	acceptNext(Scan::Value);

	nexts();
	if (sym == Scan::String)
	{
		spell = scan->getSpell();
		std::string value = spell;
		checkTypeWithContent(static_cast<SimpleType *>(arr->type)->type, value);
		objectManager.addToArraySimpleType(arr, value);
	}
	else if (sym == Scan::Array)
	{
		if (dynamic_cast<Structure*>((arr->type)) == nullptr)
			printError("There should be SimpleType variable");
		Structure* structure = objectManager.addToArrayStructure(arr);
		acceptVarStructure(structure);
	}
	else {
		std::string err = "Error: Missing Quotes?";
		printError(err);
	}

	acceptNext(Scan::EndObject);
	nexts();
	return sym == Scan::Comma;
}

void Parser::acceptVar()
{
	acceptNext(Scan::Value);
	acceptNext(Scan::String);

	spell = scan->getSpell();
	std::string type = spell;

	if (!objectManager.existsType(type)) 
	{
		std::string err = "Undeclared variable type: " + type +"\n";
		printError(err);
	}

	acceptNext(Scan::Comma);

	acceptNext(Scan::String, "name");
	acceptNext(Scan::Value);
	acceptNext(Scan::String);

	spell = scan->getSpell();
	std::string name = spell;
	acceptNext(Scan::Comma);

	acceptNext(Scan::String, "data");
	acceptNext(Scan::Value);
	nexts();

	if (objectManager.isSimpleType(type)) {
		spell = scan->getSpell();
		std::string data = spell;
		checkTypeWithContent(type, data);
		objectManager.addSimpleTypeVariable(name, type, data);
	}
	else if (objectManager.existsStructureType(type)) {
		accept(Scan::Array);
		Structure * structure = objectManager.addStructureVariable(name, type);
		acceptVarStructure(structure);
	}
	else {
		std::string err = "Error: Missing Quotes?";
		printError(err);
	}
	nexts();
}
void Parser::acceptVarStructure(Structure *structure) {
	acceptVarStructureValues(structure);
	accept(Scan::EndArray);
}
void Parser::acceptVarStructureValues(Structure* structure)
{
	while (acceptVarStructureValue(structure));
}
bool Parser::acceptVarStructureValue(Structure *structure) {
	acceptNext(Scan::Object);

	acceptNext(Scan::String, "attrib");
	acceptNext(Scan::Value);
	acceptNext(Scan::String);

	spell = scan->getSpell();
	std::string name = spell;

	Structure* structInStruct = (Structure*)objectManager.findStructureByField(structure, name);
	if (structInStruct == nullptr) 
	{
		std::string err = "Struct field " + name + " does not exists in " + structure->structType;
		printError(err);
	}

	Object *obj = objectManager.findStructureByField(structure, name);
	if (obj->isInitialized()) {
		printError("Field with name \""+ name + "\" is initialized.");
	}

	acceptNext(Scan::Comma);

	acceptNext(Scan::String, "value");
	acceptNext(Scan::Value);
	nexts();

	if (sym == Scan::String) {
		spell = scan->getSpell();
		std::string value = spell;
		checkTypeWithContent(static_cast<SimpleType*>(obj)->type, value);
		obj->setValue(value);
	}
	else if (sym == Scan::Array) {
		structInStruct->name = name;
		acceptVarStructure(structInStruct);
	}
	else {
		std::string err = "Error: Missing Quotes?";
		printError(err);
	}

	acceptNext(Scan::EndObject);

	nexts();
	return sym == Scan::Comma;
}