#include "ObjectManager.h"



ObjectManager::ObjectManager()
{
	declaredSimpleTypes.push_back("int");
	declaredSimpleTypes.push_back("double");
	declaredSimpleTypes.push_back("float");
	declaredSimpleTypes.push_back("string");
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


void ObjectManager::writeAll()
{
	
	for (unsigned i = 0; i < models.size(); ++i)
	{
		models[i]->write();
		std::cout << std::endl;
	}
	
	
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
