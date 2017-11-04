#include "TiledEntity.h"



TiledEntity::TiledEntity()
{
}


TiledEntity::~TiledEntity()
{
}

bool TiledEntity::isTiled()
{
	return true;
}

void TiledEntity::setTileMapArea(sf::IntRect tileMapArea)
{
	this->tileMapArea = tileMapArea;
}

void TiledEntity::setSubTextures(std::vector<std::vector<sf::IntRect>> subTextures)
{
	this->subTextures = subTextures;
}

tinyxml2::XMLDocument* TiledEntity::saveToFile()
{
	using namespace tinyxml2;
	XMLDocument *xmlDoc = new XMLDocument;

	XMLNode * pRoot = xmlDoc->NewElement("Root");
	xmlDoc->InsertFirstChild(pRoot);

	XMLElement * pElement = xmlDoc->NewElement("ObjectType");
	pElement->SetText("TiledEntity");
	pRoot->InsertEndChild(pElement);

	pElement = xmlDoc->NewElement("RenderPosition");
	pElement->SetText(getRenderPos());
	pRoot->InsertEndChild(pElement);

	pElement = xmlDoc->NewElement("Tag");
	pElement->SetText(getTag().c_str());
	pRoot->InsertEndChild(pElement);
	//////////////////////TILED ENTITY//////////////////////////////
	pElement = xmlDoc->NewElement("tiledMapArea");
	pElement->SetAttribute("left", tileMapArea.left);
	pElement->SetAttribute("top", tileMapArea.top);
	pElement->SetAttribute("width", tileMapArea.width);
	pElement->SetAttribute("height", tileMapArea.height);
	pRoot->InsertEndChild(pElement);

	pElement = xmlDoc->NewElement("subTextures");
	for (auto it : subTextures)
	{ 
		for (const auto & item : it)
		{
		XMLElement * pListElement = xmlDoc->NewElement("Item");
		pListElement->SetAttribute("left",item.left);
		pListElement->SetAttribute("top", item.top);
		pListElement->SetAttribute("width", item.width);
		pListElement->SetAttribute("height", item.height);
		pElement->InsertEndChild(pListElement);
		}
	}
	pRoot->InsertEndChild(pElement);
	return xmlDoc;
}
