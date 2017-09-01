#pragma once
#include "BaseEntity.h"

class SpriteEntity : public BaseEntityExp
{
public:
	SpriteEntity();
	virtual ~SpriteEntity();

	sf::Sprite* getSprite();
	int getRenderPos();
	void setTexture(const sf::Texture  & texture);

	void setRenderPos(int renderPos);
	bool isRenderable();
	void setPosition(int x, int y);

	void setWidthHeight(int width, int height);

protected:

	int getWidth();
	int getHeight();

	sf::Sprite sprite;

	Coord worldPosition;
private:
	int renderPos;
	bool isOnTileMap;
};

