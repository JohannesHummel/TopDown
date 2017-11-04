#pragma once
#include "BaseEntity.h"
#include "tinyxml2.h"

class SpriteEntity : public BaseEntityExp
{
public:
	SpriteEntity();
	virtual ~SpriteEntity();

	sf::Sprite* getSprite();
	int getRenderPos();
	void setTexture(const sf::Texture  & texture);
	void setTextureName(const std::string &textureName);
	std::string getTextureName();

	void setRenderPos(int renderPos);
	bool isRenderable();
	void setPosition(int x, int y);
	sf::Vector2f SpriteEntity::getPosition();

	void setWidthHeight(int width, int height);

	virtual tinyxml2::XMLDocument* saveToFile();
	virtual void loadFromFile(const RessourceManager & ressourceManager);

protected:

	int getWidth();
	int getHeight();

	sf::Sprite sprite;

	Coord worldPosition;
private:
	int renderPos;
	std::string textureName;
};

