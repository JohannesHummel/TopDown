#include "SpriteEntity.h"


SpriteEntity::SpriteEntity() : renderPos(0), isOnTileMap(false)
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

int SpriteEntity::getWidth()
{
	return getSprite()->getGlobalBounds().width;
}

int SpriteEntity::getHeight()
{
	return getSprite()->getGlobalBounds().height;
}
