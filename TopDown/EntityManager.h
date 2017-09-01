#pragma once
#include <map>
#include <memory>
#include <string>
//#include <tuple>

#include <queue>
#include <SFML\Window.hpp>
#include "Framework.h"
#include "TiledMap.h"
#include "TileMap.h"

class BaseEntityExp;




class EntityManager
{
	friend class Framework;
public:
	EntityManager(sf::RenderWindow & window);
	~EntityManager();

	void insertEntity(std::shared_ptr<BaseEntityExp> toInsert);

	Coord fromTiledToWorldCoordinates(unsigned int xCoord, unsigned int yCoord, unsigned int widthAmountOfTiles, unsigned int heightAmountOfTiles);

	void setTileMap(TileMap* tM);

private:

	void render();
	void update(float deltaTime);

	//linked list instead vector ? 
	std::map<std::string, std::vector<std::shared_ptr<BaseEntityExp>>> entities;

	struct Comperator
	{
		bool operator()(std::shared_ptr<BaseEntityExp> a, std::shared_ptr<BaseEntityExp> b);
	};

	std::priority_queue<std::shared_ptr<BaseEntityExp>, std::vector<std::shared_ptr<BaseEntityExp>>, Comperator> renderSequence;
	
	sf::RenderWindow& window;

	TiledMap tiledForeground;
	TiledMap tiledBackground;


	TileMap* tileMap;
};

