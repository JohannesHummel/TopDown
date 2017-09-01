#include "AnimatedEntityTest.h"
#include <iostream>



void AnimatedEntityTest::onCreate()
{
	//setWidthHeight(800, 300);

}

void AnimatedEntityTest::update(float deltaTime)
{
	applyAnimation("walkDown");
	move(deltaTime);

}

void AnimatedEntityTest::move(float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		sprite.move(-1 * deltaTime, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		sprite.move(1 * deltaTime, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		sprite.move(0, -1 * deltaTime);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		sprite.move(0, 1 * deltaTime);
	}
}

