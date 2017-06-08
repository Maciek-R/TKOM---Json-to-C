#include "ObjectManager.h"



ObjectManager::ObjectManager()
{
	declaredSimpleTypes.push_back("int");
	declaredSimpleTypes.push_back("double");
	declaredSimpleTypes.push_back("float");
	declaredSimpleTypes.push_back("string");
}

void ObjectManager::addStructureType(Structure * structure)
{
	structures.push_back(structure);
}
bool ObjectManager::existsStructureType(std::string structureType)
{
	for (Structure* structure : structures)
	{
		if (structure->getStructType() == structureType)
			return true;
	}
	return false;
}
bool ObjectManager::existsStructField(Structure* structure, std::string name)
{
	for (Object* obj : structure->fields)
	{
		if (obj->name == name)
			return true;
	}
	return false;
}
bool ObjectManager::existsType(std::string type)
{
	return existsStructureType(type) || isSimpleType(type);
}
void ObjectManager::addStructureField(Structure* structure, std::string name, std::string type)
{
	Object* field = getType(type);
	field->name = name;
	structure->fields.push_back(field);
}

Object* ObjectManager::getType(std::string type)
{
	if (isSimpleType(type)) {
		return new SimpleType(type);
	}
	else if (existsStructureType(type))
	{
		return findStructureByType(type)->clone();
	}
	else {
		std::cout << "This type: " + type +" does not exists" << std::endl;
		return nullptr;
	}

}
bool ObjectManager::isSimpleType(std::string type)
{
	for (std::string simpleType : declaredSimpleTypes)
	{
		if (simpleType == type)
			return true;
	}
	return false;
}

Structure* ObjectManager::findStructureByType(std::string type)
{
	for (Structure* structure : structures)
	{
		if (structure->getStructType() == type)
			return structure;
	}
	return nullptr;
}
Object* ObjectManager::findStructureByField(Structure* structure, std::string name)
{
	for (Object* obj : structure->fields)
	{
		if (obj->name == name)
			return obj;
	}
	return nullptr;
}

void ObjectManager::addSimpleTypeVariable(std::string name, std::string type, std::string data)
{
	SimpleType *var = new SimpleType(type);
	var->name = name;
	var->val = data;
	objects.push_back(var);
}

Structure* ObjectManager::addStructureVariable(std::string name, std::string type)
{
	Structure *structure = findStructureByType(type);
	Structure *clonedStructure = structure->clone();
	clonedStructure->name = name;
	objects.push_back(clonedStructure);
	return clonedStructure;
}

Array* ObjectManager::addArrayVariable(std::string name, std::string type)
{
	Object *obj = getType(type);
	obj->name = type;
	Array* arr = new Array(obj, name);
	objects.push_back(arr);
	return arr;
}

void ObjectManager::addToArraySimpleType(Array* array, std::string value)
{
	Object* obj = array->type->clone();
	obj->setValue(value);
	array->elements.push_back(obj);
}
Structure* ObjectManager::addToArrayStructure(Array* arr)
{
	Structure* structure = (Structure*)arr->type->clone();
	arr->elements.push_back(structure);
	return structure;
}

//----------------------------------------------------------------

void ObjectManager::writeAll(std::string outputFile)
{
	std::fstream file;
	file.open(outputFile, std::ios::out);
	
	for (Structure* structure : structures)
	{
		structure->writeDeclaration(file);
		file << "\n";
	}
	for (Object* obj : objects)
	{
		obj->write(file);
		file << "\n";
	}
	

	file.close();
}
