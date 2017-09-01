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
