#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <array>
#include <vector>
#include <iostream>
#include "BaseEntity.h"
#include "tinyxml2.h"


struct DataType
{
	/////////BASE ENTITY////////////
	std::string objectType;
	int renderPos;
	std::string tag;
	/////////SPRITE ENTITY////////////
	std::array<int, 2> position;
	std::array<int, 2> size;
	std::string textureName;
	/////////ANIMATED ENTITY////////////
	float switchAnimationTime;
	std::string animationName;
	std::vector<int> animationRect;
	/////////TILED ENTITY////////////
	sf::IntRect tileMapArea;
	std::vector<int> subTextures;

	/*bool hasPosition = false;
	
	bool hasPositionInTiledMap = false;
	std::array<int, 2> positionInTiledMap;
	bool hasTexture = false;
	
	bool hasAnimation = false;
	int amountOfAnimations;
	std::vector<int> defaultSprite;*/
};

class RessourceManager
{
public:
	RessourceManager();
	~RessourceManager();
	void readFromFile(std::string const &filename);
	void writeInFile(std::string const &filename, BaseEntityExp  &baseEntity);

	void readBaseEntity(const std::string & filename);
	void readSpriteEntity(const std::string & filename);
	void readAnimatedEntity(const std::string &filename);
	void readTiledEntity(const std::string &filename);

	DataType getData() const;
private:
	DataType data;
};

