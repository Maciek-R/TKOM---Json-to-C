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
	for (Structure* structure : structures)
	{
		if (structure->getName() == name)
			return true;
	}
	return false;
}
bool ObjectManager::existsType(std::string type)
{
	//return isSimpleType(type)
	//	|| isDefinedType(type)
	//	|| isStructureType(type);
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
		return findStructure(type)->clone();
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

Structure* ObjectManager::findStructure(std::string type)
{
	for (Structure* structure : structures)
	{
		if (structure->getStructType() == type)
			return structure;
	}
	return nullptr;
}

void ObjectManager::addSimpleTypeVariable(std::string name, std::string type, std::string data)
{
	SimpleType *var = new SimpleType(type);
	var->name = name;
	var->value = data;
	objects.push_back(var);
}



//----------------------------------------------------------------

void ObjectManager::writeAll(std::string outputFile)
{
	std::fstream file;
	file.open(outputFile, std::ios::out);
	/*for (unsigned i = 0; i < models.size(); ++i)
	{
		models[i]->write(file);
		std::cout << std::endl;
	}*/
	for (Structure* structure : structures)
		structure->writeDeclaration(file);

	for (Object* obj : objects)
		obj->write(file);
	

	file.close();
}
/*void ObjectManager::addModel(Model*m)
{
	models[models.size() - 1]->addModel(m);
}

void ObjectManager::addArray()
{
	models.push_back(new Model(Model::Typ::Array));
}
void ObjectManager::setType(char* type)
{
	models[models.size()-1]->setType(type);
	for (unsigned i = 0; i < declaredSimpleTypes.size(); ++i)
	{
		if (declaredSimpleTypes[i] == type)
		{
			models[models.size() - 1]->setSimpleType(true);
			return;
		}
	}
	models[models.size() - 1]->setSimpleType(false);
}
void ObjectManager::setName(char* name)
{
	models[models.size() - 1]->setName(name);
}
void ObjectManager::addArrayValue(char* value)
{
	models[models.size() - 1]->addValue(value);
}


void ObjectManager::addStructDeclaration()
{
	models.push_back(new Model(Model::Typ::Structure));
	
}
void ObjectManager::setStructTypeName(char * structTypeName)
{
	models[models.size() - 1]->setStructTypeName(structTypeName);
}
void ObjectManager::setStructFieldName(char * structFieldName)
{
	models[models.size() - 1]->setStructFieldName(structFieldName);
}
void ObjectManager::setStructFieldType(char * structFieldType)
{
	models[models.size() - 1]->setStructFieldType(structFieldType);
}
Model* ObjectManager::getStructureWithTypeName(std::string typeName)
{
	for (unsigned i = 0; i < models.size(); ++i)
	{
		if (models[i]->typ == Model::Structure) {
			if (strcmp(typeName.c_str(), models[i]->getName()) == 0)
			{
				return models[i];
			}
		}
	}
}



void ObjectManager::addVariable()
{
	models.push_back(new Model(Model::Typ::Var));
}
void ObjectManager::setVariableData(char* data)
{
	models[models.size() - 1]->setVariableData(data);
}
bool ObjectManager::isSimpleType()
{
	return models[models.size() - 1]->isSimpleType();
}


void ObjectManager::writeAll(std::string outputFile)
{
	std::fstream file;
	file.open(outputFile, std::ios::out);
	for (unsigned i = 0; i < models.size(); ++i)
	{
		models[i]->write(file);
		std::cout << std::endl;
	}
	
	file.close();
}

bool ObjectManager::checkIfTypeIsExisting(std::string type)
{
	for (unsigned i = 0; i < declaredSimpleTypes.size(); ++i)
	{
		if (declaredSimpleTypes[i] == type) 
			return true;
	}
	for (unsigned i = 0; i < declaredOwnTypes.size(); ++i)
	{
		if (declaredOwnTypes[i] == type)
			return true;
	}
	return false;
}
void ObjectManager::addNewType(std::string type)
{
	declaredOwnTypes.push_back(type);
}

*/