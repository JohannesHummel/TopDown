#include "BaseEntity.h"
#include "RessourceManager.h"



BaseEntity::BaseEntity(const sf::Texture  & texture, sf::Vector2f &size, EntityManager* eM) : sprite(texture), tag(""), entityManager(eM)
{
	this->setWidthHeight(size.x,size.y);
	//sprite.scale(size);
}


BaseEntity::~BaseEntity()
{
}

sf::Vector2f BaseEntity::getPosition()
{
	return sprite.getPosition();
}

void BaseEntity::setPosition(sf::Vector2f pos)
{
	sprite.setPosition(pos);
}

void BaseEntity::setRenderPos(int rPos)
{
	renderPos = rPos;
}

sf::Sprite* BaseEntity::getSprite()
{
	return &sprite;
}

int BaseEntity::getRenderPos()
{
	return renderPos;
}

std::string BaseEntity::getTag()
{
	return tag;
}

void BaseEntity::setWidth(int width)
{
	sprite.setScale(
		width / getSprite()->getLocalBounds().width,
		this->width / getSprite()->getLocalBounds().height);
}

void BaseEntity::setHeight(int height)
{
	sprite.setScale(
		this->height / getSprite()->getLocalBounds().width,
		height / getSprite()->getLocalBounds().height);
}

void BaseEntity::setWidthHeight(int width, int height)
{
	sprite.setScale(
		width / getSprite()->getLocalBounds().width,
		height / getSprite()->getLocalBounds().height);
}

int BaseEntity::getWidth()
{
	return getSprite()->getGlobalBounds().width;
}

int BaseEntity::getHeight()
{
	return getSprite()->getGlobalBounds().height;
}




BaseEntityExp::BaseEntityExp() : toDelete(false)
{
}

void BaseEntityExp::setEntityManager(EntityManager * entityManager)
{
	this->entityManager = entityManager;
}

BaseEntityExp::~BaseEntityExp()
{
	entityManager = nullptr;
}

void BaseEntityExp::masterUpdate(float deltaTime)
{
	update(deltaTime);
}

bool BaseEntityExp::isRenderable()
{
	return false;
}

bool BaseEntityExp::isTiled()
{
	return false;
}

sf::Sprite* BaseEntityExp::getSprite()
{
	return nullptr;
}

int BaseEntityExp::getRenderPos()
{
	return 0;
}

tinyxml2::XMLDocument* BaseEntityExp::saveToFile()
{
	using namespace tinyxml2;
	XMLDocument *xmlDoc = new XMLDocument;

	XMLNode * pRoot = xmlDoc->NewElement("Root");
	xmlDoc->InsertFirstChild(pRoot);

	XMLElement * pElement = xmlDoc->NewElement("ObjectType");
	pElement->SetText("BaseEntity");
	pRoot->InsertEndChild(pElement);

	pElement = xmlDoc->NewElement("RenderPosition");
	pElement->SetText(getRenderPos());
	pRoot->InsertEndChild(pElement);

	pElement = xmlDoc->NewElement("Tag");
	pElement->SetText(getTag().c_str());
	pRoot->InsertEndChild(pElement);

	return xmlDoc;
}

void BaseEntityExp::loadFromFile(const RessourceManager & ressourceManager)
{
	this->setTag(ressourceManager.getData().tag);
}

std::string & BaseEntityExp::getTag()
{
	return tag;
}

void BaseEntityExp::setTag(const std::string & tag)
{
	this->tag = tag;
}

void BaseEntityExp::deleteEntity()
{
	toDelete = true;
}

bool BaseEntityExp::shouldBeDeleted()
{
	return toDelete;
}
