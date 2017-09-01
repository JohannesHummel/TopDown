#include "EntityManager.h"

#include "BaseEntity.h"
#include "SpriteEntity.h"
#include "TiledEntity.h"


typedef std::pair<std::string, std::vector<std::shared_ptr<BaseEntityExp>>> lmPair;




EntityManager::EntityManager(sf::RenderWindow & window) : window(window), tiledBackground(1,30), tiledForeground(10, 300)
{	
}

EntityManager::~EntityManager()
{
}

void EntityManager::insertEntity(std::shared_ptr<BaseEntityExp> toInsert)
{
	toInsert->onCreate();
	auto it = entities.find(toInsert->getTag());
	if (it != entities.end())
	{
		it->second.push_back(toInsert);
	}
	else
	{
		std::vector<std::shared_ptr<BaseEntityExp>> newVector;
		newVector.push_back(toInsert);
		entities.insert(lmPair(toInsert->getTag(),newVector));
	}

	if (toInsert->isRenderable())
	{
		//std::shared_ptr<SpriteEntity> spriteEntity = std::static_pointer_cast<SpriteEntity>(toInsert);
		//Coord tmpCoord = spriteEntity->getTiledMapPosition();
		//tiledForeground.insert(toInsert->getTag(),tmpCoord);
	}

	if (toInsert->isTiled())
	{
		std::shared_ptr<TiledEntity> tE = std::static_pointer_cast<TiledEntity>(toInsert);
		tileMap->insertTiledEntity(*tE.get());
	}
}

Coord EntityManager::fromTiledToWorldCoordinates(unsigned int xCoord, unsigned int yCoord, unsigned int widthAmountOfTiles, unsigned int heightAmountOfTiles)
{
	return tiledForeground.getRealCoordinates(xCoord, yCoord,widthAmountOfTiles, heightAmountOfTiles);
}


void EntityManager::setTileMap(TileMap* tM)
{
	this->tileMap = tM;
}



void EntityManager::render()
{

	while (!renderSequence.empty())
	{
		window.draw(*renderSequence.top()->getSprite());
		renderSequence.pop();
	}
}



void EntityManager::update(float deltaTime)
{
	for (auto it : entities)
	{
		for (auto it2 : it.second)
		{
			it2->masterUpdate(deltaTime);

			if(it2->isRenderable())
				renderSequence.push(it2);

			if (it2->shouldBeDeleted())
			{
				//delete this entity from container
			}
		}
	}
}

bool EntityManager::Comperator::operator()(std::shared_ptr<BaseEntityExp> a, std::shared_ptr<BaseEntityExp> b)
{
	return a->getRenderPos() > b->getRenderPos();
}
