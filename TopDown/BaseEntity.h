#pragma once
#include "SFML\Graphics.hpp"
#include <memory>

#include <string>

#include "EntityManager.h"

class BaseEntity
{
public:
	BaseEntity(const sf::Texture  & texture, sf::Vector2f &size, EntityManager* eM);
	~BaseEntity();

	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos);
	void setRenderPos(int rPos);

	virtual void update(float deltaTime) = 0;

	sf::Sprite* getSprite();
	int getRenderPos();
	std::string getTag();
	//int 


private:
	sf::Sprite sprite;
	int renderPos;
	std::string tag;
	//int 
	int xCoord, yCoord, width, height;
	bool inForeground;
protected:
	EntityManager* entityManager;

	void setWidth(int width);
	void setHeight(int height);
	void setWidthHeight(int width, int height);

	int getWidth();
	int getHeight();
};

class BaseEntityExp
{
public:
	BaseEntityExp();

	void setEntityManager(EntityManager* entityManager);

	virtual ~BaseEntityExp();

	virtual void onCreate() = 0;
	virtual void masterUpdate(float deltaTime);

	virtual bool isRenderable();
	virtual bool isTiled();
	virtual sf::Sprite* getSprite();
	virtual int getRenderPos();

	std::string& getTag();
	void setTag(const std::string &tag);
	void deleteEntity();
	bool shouldBeDeleted();
protected:
	virtual void update(float deltaTime) = 0;
	EntityManager* entityManager;
private:
	std::string tag;
	bool toDelete;
};