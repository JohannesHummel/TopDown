#pragma once
#include "AnimatedEntity.h"


class AnimatedEntityTest : public AnimatedEntity
{
public:
	
	void onCreate();
	void update(float deltaTime);
private:
	void move(float deltaTime);
};

