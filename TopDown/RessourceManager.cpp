#include "RessourceManager.h"

using namespace tinyxml2;


RessourceManager::RessourceManager()
{
}


RessourceManager::~RessourceManager()
{
}


void RessourceManager::readFromFile(std::string const &filename)
{
	XMLDocument xmlDoc;
	xmlDoc.LoadFile(filename.c_str());

	XMLNode * pRoot = xmlDoc.FirstChild();
	XMLElement * pElement = pRoot->FirstChildElement("ObjectType");
	data.objectType = pElement->GetText();

	if (data.objectType == "BaseEntity")
	{
		readBaseEntity(filename);
	}
	if (data.objectType == "SpriteEntity")
	{
		readSpriteEntity(filename);
	}
	if (data.objectType == "AnimatedEntity")
	{
		readAnimatedEntity(filename);
	}
	if (data.objectType == "TiledEntity")
	{
		readTiledEntity(filename);
	}
}

void RessourceManager::writeInFile(std::string const & filename, BaseEntityExp  &baseEntity)
{
	baseEntity.saveToFile()->SaveFile(filename.c_str());
}

void RessourceManager::readBaseEntity(const std::string & filename)
{
	XMLDocument xmlDoc;
	xmlDoc.LoadFile(filename.c_str());

	XMLNode * pRoot = xmlDoc.FirstChild();
	XMLElement * pElement = pRoot->FirstChildElement("ObjectType");
	data.objectType = pElement->GetText();

	pElement = pRoot->FirstChildElement("RenderPosition");
    pElement->QueryIntText(&data.renderPos);

	pElement = pRoot->FirstChildElement("Tag");
	data.tag = pElement->GetText();

}

void RessourceManager::readSpriteEntity(const std::string & filename)
{
	readBaseEntity(filename);

	XMLDocument xmlDoc;
	xmlDoc.LoadFile(filename.c_str());

	XMLNode * pRoot = xmlDoc.FirstChild();
	XMLElement * pElement = pRoot->FirstChildElement("worldPosition");
	pElement->QueryIntAttribute("x", &data.position[0]);
	pElement->QueryIntAttribute("y", &data.position[1]);


	pElement = pRoot->FirstChildElement("size");
	pElement->QueryIntAttribute("width", &data.size[0]);
	pElement->QueryIntAttribute("height", &data.size[1]);

	pElement = pRoot->FirstChildElement("textureName");
	data.textureName = pElement->GetText();

}

void RessourceManager::readAnimatedEntity(const std::string & filename)
{
	readSpriteEntity(filename);

	XMLDocument xmlDoc;
	xmlDoc.LoadFile(filename.c_str());

	XMLNode * pRoot = xmlDoc.FirstChild();

	XMLElement * pElement = pRoot->FirstChildElement("switchAnimationTime");
	pElement->QueryFloatText(&data.switchAnimationTime);


	pElement = pRoot->FirstChildElement("Animations");
	XMLElement * pListElement = pElement->FirstChildElement("Item");
	while (pListElement != nullptr)
	{
		int iOutListValue;
		pListElement->QueryIntText(&iOutListValue);
		data.subTextures.push_back(iOutListValue);
		pListElement = pListElement->NextSiblingElement("Item");
	}

}

void RessourceManager::readTiledEntity(const std::string &filename)
{
	readBaseEntity(filename);

	XMLDocument xmlDoc;
	xmlDoc.LoadFile(filename.c_str());

	XMLNode * pRoot = xmlDoc.FirstChild();
	XMLElement * pElement = pRoot->FirstChildElement("tiledMapArea");
	pElement->QueryIntAttribute("left", &data.tileMapArea.left);
	pElement->QueryIntAttribute("top", &data.tileMapArea.top);
	pElement->QueryIntAttribute("width", &data.tileMapArea.width);
	pElement->QueryIntAttribute("height", &data.tileMapArea.height);


	pElement = pRoot->FirstChildElement("subTextures");
	XMLElement * pListElement = pElement->FirstChildElement("Item");
	while (pListElement != nullptr)
	{
		int iOutListValue;
		pListElement->QueryIntText(&iOutListValue);
		data.subTextures.push_back(iOutListValue);
		pListElement = pListElement->NextSiblingElement("Item");
	}
}


 DataType RessourceManager::getData() const
{
	return data;
}

