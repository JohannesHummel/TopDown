#include "SpriteEntity.h"
#include "RessourceManager.h"


SpriteEntity::SpriteEntity() : renderPos(0)
{
}


SpriteEntity::~SpriteEntity()
{
}

sf::Sprite * SpriteEntity::getSprite()
{
	return &sprite;
}

int SpriteEntity::getRenderPos()
{
	return renderPos;
}

void SpriteEntity::setTexture(const sf::Texture & texture)
{
	sprite.setTexture(texture);
}

void SpriteEntity::setTextureName(std::string const &textureName)
{
	this->textureName = textureName;
}

std::string SpriteEntity::getTextureName()
{
	return textureName;
}

void SpriteEntity::setRenderPos(int renderPos)
{
	this->renderPos = renderPos;
}


bool SpriteEntity::isRenderable()
{
	return true;
}

void SpriteEntity::setPosition(int x, int y)
{
	worldPosition.x = x; 
	worldPosition.y = y;

	sprite.setPosition(x, y);
}

void SpriteEntity::setWidthHeight(int width, int height)
{
	sprite.setScale(
		width / getSprite()->getLocalBounds().width,
		height / getSprite()->getLocalBounds().height);
	worldPosition.width = width;
	worldPosition.height = height;
}

tinyxml2::XMLDocument* SpriteEntity::saveToFile()
{
	using namespace tinyxml2;
	XMLDocument *xmlDoc = new XMLDocument;

	XMLNode * pRoot = xmlDoc->NewElement("Root");
	xmlDoc->InsertFirstChild(pRoot);

	XMLElement * pElement = xmlDoc->NewElement("ObjectType");
	pElement->SetText("SpriteEntity");
	pRoot->InsertEndChild(pElement);

	pElement = xmlDoc->NewElement("RenderPosition");
	pElement->SetText(getRenderPos());
	pRoot->InsertEndChild(pElement);

	pElement = xmlDoc->NewElement("Tag");
	pElement->SetText(getTag().c_str());
	pRoot->InsertEndChild(pElement);
	/////////////////////SPRITE ENTITY/////////////////////////////
	pElement = xmlDoc->NewElement("worldPosition");
	pElement->SetAttribute("x", worldPosition.x);
	pElement->SetAttribute("y", worldPosition.y);
	pRoot->InsertEndChild(pElement);

	pElement = xmlDoc->NewElement("size");
	pElement->SetAttribute("width", getWidth());
	pElement->SetAttribute("height", getHeight());
	pRoot->InsertEndChild(pElement);

	pElement = xmlDoc->NewElement("textureName");
	pElement->SetText(getTextureName().c_str());
	pRoot->InsertEndChild(pElement);
	return xmlDoc;
}

void SpriteEntity::loadFromFile(const RessourceManager & ressourceManager)
{
	BaseEntityExp::loadFromFile(ressourceManager);
	this->setRenderPos(ressourceManager.getData().renderPos);
	worldPosition.x = ressourceManager.getData().position[0];
	worldPosition.y = ressourceManager.getData().position[1];
	this->setWidthHeight(ressourceManager.getData().size[0], ressourceManager.getData().size[1]);
	this->setTextureName(ressourceManager.getData().textureName);
}

int SpriteEntity::getWidth()
{
	return getSprite()->getGlobalBounds().width;
}

int SpriteEntity::getHeight()
{
	return getSprite()->getGlobalBounds().height;
}

sf::Vector2f SpriteEntity::getPosition()
{
	return sf::Vector2f(worldPosition.x, worldPosition.y);
}
