#pragma once
#include "BaseEntity.h"
#include "tinyxml2.h"
#include <vector>

class TiledEntity : public BaseEntityExp
{
	friend class TileMap;
public:
	TiledEntity();
	virtual ~TiledEntity();
	bool isTiled();

	Coord& getWorldPos(); 
	void setTileMapArea(sf::IntRect tileMapArea);
	void setSubTextures(std::vector<std::vector<sf::IntRect>> subTextures);

	virtual tinyxml2::XMLDocument* saveToFile();

protected:
	sf::IntRect tileMapArea;
	std::vector<std::vector<sf::IntRect>> subTextures;
	Coord worldPosition;
};

