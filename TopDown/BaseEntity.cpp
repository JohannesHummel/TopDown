#include "BaseEntity.h"



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
