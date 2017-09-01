#include "AnimatedEntityTest.h"
#include <iostream>



void AnimatedEntityTest::onCreate()
{
	//setWidthHeight(800, 300);

}

void AnimatedEntityTest::update(float deltaTime)
{
	applyAnimation("walkDown");
}
