#include "ObjectManager.h"



ObjectManager::ObjectManager()
{
	
}

void ObjectManager::addArray()
{
	models.push_back(new Model(Model::Typ::Array));
}
void ObjectManager::setType(char* type)
{
	models[models.size()-1]->setType(type);
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


void ObjectManager::writeAll()
{
	
	for (unsigned i = 0; i < models.size(); ++i)
	{
		models[i]->write();
		std::cout << std::endl;
	}
	
	
}