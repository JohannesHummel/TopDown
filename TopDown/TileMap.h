#pragma once

#include <SFML\Graphics.hpp>
#include <string>

class TiledEntity;

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	TileMap(sf::Texture tileset, sf::Vector2u amountOfTiles, int tileSize, const std::vector<sf::IntRect>& subTex);
	~TileMap();

	void insertTiledEntity(TiledEntity const& tiledEntity);
	void deleteTiledEntity(sf::IntRect const& texturedArea);

private:
	void initTileMap();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::VertexArray vertices;
	sf::Texture tileset;
	sf::Vector2u amountOfTiles;
	int tileSize;

	std::vector<sf::IntRect> subTex;
};

