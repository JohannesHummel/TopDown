#include "TileMap.h"
#include "TiledEntity.h"

#define VERTICESPERQUAD 4


TileMap::TileMap(sf::Texture tileset, sf::Vector2u amountOfTiles, int tileSize, const std::vector<sf::IntRect>& subTex) :
	tileset (tileset), amountOfTiles(amountOfTiles), tileSize(tileSize), subTex(subTex)
{
	initTileMap();
}


TileMap::~TileMap()
{
}

//TODO check if index is out of bound.
void TileMap::insertTiledEntity(TiledEntity const& tiledEntity)
{
	int left = tiledEntity.tileMapArea.left;
	int top = tiledEntity.tileMapArea.top;
	int width = tiledEntity.tileMapArea.width;
	int height = tiledEntity.tileMapArea.height;

	int absWidth = width + left;
	int absHeight = height + top;

	//for (int x = 0; x < tiledEntity.subTextures.size(); ++x)
		//for (int y = 0; y < tiledEntity.subTextures[x].size(); ++y)
	for (int x = left; x < absWidth; ++x)
		for (int y = top; y < absHeight; ++y)
		{
			sf::Vertex* quad = &vertices[(x + y * amountOfTiles.x) * VERTICESPERQUAD];
			//sf::Vertex* quad = &vertices[(tiledEntity.tileMapArea.left + x + tiledEntity.tileMapArea.top +y * amountOfTiles.x) * 4];
			quad->color = sf::Color::Blue;

			int texCoordX = x - left;
			int texCoordY = y - top;

			quad[0].texCoords = sf::Vector2f(tiledEntity.subTextures[texCoordX][texCoordY].left, tiledEntity.subTextures[texCoordX][texCoordY].top);
			quad[1].texCoords = sf::Vector2f(tiledEntity.subTextures[texCoordX][texCoordY].left + tiledEntity.subTextures[texCoordX][texCoordY].width, tiledEntity.subTextures[texCoordX][texCoordY].top);
			quad[2].texCoords = sf::Vector2f(tiledEntity.subTextures[texCoordX][texCoordY].left + tiledEntity.subTextures[texCoordX][texCoordY].width, tiledEntity.subTextures[texCoordX][texCoordY].top + tiledEntity.subTextures[texCoordX][texCoordY].height);
			quad[3].texCoords = sf::Vector2f(tiledEntity.subTextures[texCoordX][texCoordY].left, tiledEntity.subTextures[texCoordX][texCoordY].top + tiledEntity.subTextures[texCoordX][texCoordY].height);	
		}
}

void TileMap::deleteTiledEntity(sf::IntRect const & texturedArea)
{
	int subTexIndex = texturedArea.left * texturedArea.top;
	sf::IntRect currentSubTex;
	for(int x = texturedArea.left; x < texturedArea.width; ++x)
		for (int y = texturedArea.top; y < texturedArea.height; ++y)
		{
			sf::Vertex* quad = &vertices[(x + y * amountOfTiles.x) * 4];

			currentSubTex = subTex.at(subTexIndex);

			quad[0].texCoords = sf::Vector2f(currentSubTex.left, currentSubTex.top);
			quad[1].texCoords = sf::Vector2f(currentSubTex.left + currentSubTex.width, currentSubTex.top);
			quad[2].texCoords = sf::Vector2f(currentSubTex.left + currentSubTex.width, currentSubTex.top + currentSubTex.height);
			quad[3].texCoords = sf::Vector2f(currentSubTex.left, currentSubTex.top + currentSubTex.height);

			subTexIndex++;
		}
}

//TODO: control size of vector
void TileMap::initTileMap()
{
	vertices.setPrimitiveType(sf::Quads);
	vertices.resize(amountOfTiles.x * amountOfTiles.y * VERTICESPERQUAD);
	int subTexIndex = 0;
	sf::IntRect currentSubTex;
	for(int x = 0; x < amountOfTiles.x; ++x)
		for (int y = 0; y < amountOfTiles.y; ++y)
		{
			sf::Vertex* quad = &vertices[(x + y * amountOfTiles.x) * VERTICESPERQUAD];

			quad[0].position = sf::Vector2f(x * tileSize, y * tileSize);
			quad[1].position = sf::Vector2f((x + 1) * tileSize, y * tileSize);
			quad[2].position = sf::Vector2f((x + 1) * tileSize, (y + 1) * tileSize);
			quad[3].position = sf::Vector2f(x * tileSize, (y + 1) * tileSize);

			currentSubTex = subTex.at(subTexIndex);

			quad[0].texCoords = sf::Vector2f(currentSubTex.left, currentSubTex.top);
			quad[1].texCoords = sf::Vector2f(currentSubTex.left + currentSubTex.width, currentSubTex.top);
			quad[2].texCoords = sf::Vector2f(currentSubTex.left + currentSubTex.width, currentSubTex.top + currentSubTex.height);
			quad[3].texCoords = sf::Vector2f(currentSubTex.left, currentSubTex.top + currentSubTex.height);
			subTexIndex++;
		}
}


void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &tileset;
	target.draw(vertices, states);
}