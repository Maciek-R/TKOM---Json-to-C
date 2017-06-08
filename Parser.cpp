#include "Parser.h"

Parser::Parser(Scan * scan)
{
	this->scan = scan;

	//exps.push_back(Scan::Object);
}

void Parser::start()
{

	acceptModule();
	
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
	

	//tree.write();
}

void Parser::writeAllToFile(std::string outputFile)
{
	objectManager.writeAll(outputFile);
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

	if (strcmp(spell, "sequenceName") == 0){
		acceptSequenceName();
	}
	else if (strcmp(spell, "array") == 0) {
		acceptArray();
	}
	else if (strcmp(spell, "variable") == 0){
		acceptVar();
	}
	else {
		std::cout << "Niepoprawny typ. Oczekiwano sequenceName, array lub variable. Line: " << scan->getLine() << std::endl;
		_getch();
		exit(0);
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

	if (objectManager.existsStructureType(type)) {
		std::cout << "Structure type already defined!" << std::endl;
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

	if (objectManager.existsStructField(structure, name)) {
		std::cout <<"Structure field with name: " + name + " already exists." << std::endl;
	}

	acceptNext(Scan::Comma);

	acceptNext(Scan::String, "type");
	acceptNext(Scan::Value);
	acceptNext(Scan::String);

	spell = scan->getSpell();
	std::string type = spell;

	if (!objectManager.existsType(type)) {
		std::cout << "Structure field type " + type + " doesn't exists" << std::endl;
	}
	
	objectManager.addStructureField(structure, name, type);

	acceptNext(Scan::EndObject);
	nexts();
	return sym == Scan::Comma;
}
void Parser::acceptArray() {

	acceptNext(Scan::Value);
	acceptNext(Scan::String);
	spell = scan->getSpell();//nie ma tutaj sprawdzania typu???
	std::string type = spell;
	acceptNext(Scan::Comma);

	//parsePairString(KeyWord::NAME);
	acceptNext(Scan::String, "name");
	acceptNext(Scan::Value);
	acceptNext(Scan::String);
	spell = scan->getSpell();
	std::string name = spell;
	acceptNext(Scan::Comma);

	//values
	acceptNext(Scan::String, "values");
	acceptNext(Scan::Value);

	

	//Array * array = manager.addArrayVariable(arrayName, arrayType);
	//parseArrayElements(array);
	acceptArrayElements(/*array*/);

	

	nexts();
}
void Parser::acceptArrayElements(/*array*/)
{
	acceptNext(Scan::Array);
	while (acceptArrayElement(/*array*/));
	accept(Scan::EndArray);
}

bool Parser::acceptArrayElement(/*array*/)
{
	acceptNext(Scan::Object);

	acceptNext(Scan::String, "value");
	acceptNext(Scan::Value);

	nexts();
	if (sym == Scan::String)
	{
		spell = scan->getSpell();
		//manager.addArrayValueSimpleType(array, value);
	}
	else if (sym == Scan::Array)
	{

	}
	/*if (symbol.first == NUMBER || symbol.first == STRING) {
		std::string value = symbol.second;
		manager.addArrayValueSimpleType(array, value);
	}
	else if (symbol.first == ARRAY_BEG) {
		//recursive - struct in struct
		Structure *structure = manager.addArrayValueStructure(array);
		parseVariableStruct(structure);
	}*/

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

	if (!objectManager.existsType(type)) {
		std::cout<<"Undeclared variable type: " + type << std::endl;
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
		objectManager.addSimpleTypeVariable(name, type, data);
	}
	/*else if (manager.isDefinedType(varType)) {
		manager.addDefinedTypeVariable(varName, varType, data);
	}*/
	else if (objectManager.existsStructureType(type)) {
		accept(Scan::Array);
		Structure * structure = objectManager.addStructureVariable(name, type);
		acceptVarStructure(structure);
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
	if (structInStruct == nullptr) {
		std::cout << "Struct field " + name + " does not exists in " + structure->structType << std::endl;
		//error("Field struct '" + attribName + "' not found in '" + structure->m_structName + "' definition.");
	}

	Object *obj = objectManager.findStructureByField(structure, name);
	/*if (attrib->hasValue()) {
		error("Attrib '" + attribName + "' has already been defined.");
	}*/

	acceptNext(Scan::Comma);

	acceptNext(Scan::String, "value");
	acceptNext(Scan::Value);
	nexts();

	if (sym == Scan::String) {
		spell = scan->getSpell();
		std::string value = spell;
		obj->setValue(value);
	}
	else if (sym == Scan::Array) {
		structInStruct->name = name;
		acceptVarStructure(structInStruct);
		//parseVariableStruct(nestedStruct);
	}
	else {
		std::cout << "Error: Missing Quotes?" << std::endl;
	}

	acceptNext(Scan::EndObject);

	nexts();
	return sym == Scan::Comma;
}