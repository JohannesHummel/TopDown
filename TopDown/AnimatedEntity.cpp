#include "AnimatedEntity.h"
#include <iostream>
#include "RessourceManager.h"


AnimatedEntity::AnimatedEntity()
{
	currentAnimation = animationContainer.find(" ");
}


AnimatedEntity::~AnimatedEntity()
{
}

void AnimatedEntity::masterUpdate(float deltaTime)
{
	animationUpdate();
	update(deltaTime);
}

void AnimatedEntity::setSwitchAnimationTime(float switchAnimationTime)
{
	this->switchAnimationTime = switchAnimationTime;
}

void AnimatedEntity::setDefault(sf::IntRect rect)
{
	sprite.setTextureRect(rect);
}

void AnimatedEntity::storeAnimation(std::string key, std::vector<sf::IntRect> animations)
{
	animationContainer.insert(std::pair<std::string, std::vector<sf::IntRect>>(key, animations));
}

void AnimatedEntity::applyAnimation(std::string key)
{

	auto iterator = animationContainer.find(key);
	if (iterator != animationContainer.end())
	{
		this->currentAnimation = iterator;
	}
	else
	{
		std::cout << "Animation not available" << std::endl;
	}
}

tinyxml2::XMLDocument* AnimatedEntity::saveToFile()
{
	using namespace tinyxml2;
	XMLDocument *xmlDoc = new XMLDocument;

	XMLNode * pRoot = xmlDoc->NewElement("Root");
	xmlDoc->InsertFirstChild(pRoot);

	XMLElement * pElement = xmlDoc->NewElement("ObjectType");
	pElement->SetText("AnimatedEntity");
	pRoot->InsertEndChild(pElement);

	pElement = xmlDoc->NewElement("RenderPosition");
	pElement->SetText(getRenderPos());
	pRoot->InsertEndChild(pElement);

	pElement = xmlDoc->NewElement("Tag");
	pElement->SetText(getTag().c_str());
	pRoot->InsertEndChild(pElement);
	/////////////////////SPRITE ENTITY/////////////////////////////
	pElement = xmlDoc->NewElement("worldPosition");
	pElement->SetAttribute("x", worldPosition.x);
	std::cout << worldPosition.x << std::endl;
	pElement->SetAttribute("y", worldPosition.y);
	pRoot->InsertEndChild(pElement);

	pElement = xmlDoc->NewElement("size");
	pElement->SetAttribute("width", getWidth());
	pElement->SetAttribute("height", getHeight());
	pRoot->InsertEndChild(pElement);

	pElement = xmlDoc->NewElement("textureName");
	pElement->SetText(getTextureName().c_str());
	pRoot->InsertEndChild(pElement);
	////////////////////ANIMATED ENTITY////////////////////////////
	pElement = xmlDoc->NewElement("switchAnimationTime");
	pElement->SetText(switchAnimationTime);
	pRoot->InsertEndChild(pElement);

	pElement = xmlDoc->NewElement("Animations");
	
	for (auto it : animationContainer)
	{
		XMLElement *listName = xmlDoc->NewElement("animation");	
		listName->SetText(it.first.c_str());
		for (auto it2 : it.second)
		{
			XMLElement * pListElement = xmlDoc->NewElement("Item");
			pListElement->SetAttribute("left", it2.left);
			pListElement->SetAttribute("top", it2.top);
			pListElement->SetAttribute("width", it2.width);
			pListElement->SetAttribute("height", it2.height);
			pElement->InsertEndChild(pListElement);
			listName->InsertEndChild(pListElement);
			pElement->InsertEndChild(listName);
		}
	}
	pRoot->InsertEndChild(pElement);
	
	/*std::string output;
	//////////////////////BASE ENTITY//////////////////////////////
	output += "AnimatedEntity\n";
	output += std::to_string(getRenderPos()) + "\n";
	output += getTag() + "\n";
	/////////////////////SPRITE ENTITY/////////////////////////////
	output += std::to_string(worldPosition.x) + " " + std::to_string(worldPosition.y) + "\n";
	output += std::to_string(getWidth()) + " " + std::to_string(getHeight()) + "\n";
	output += getTextureName() + "\n";
	////////////////////ANIMATED ENTITY////////////////////////////
	output += std::to_string(switchAnimationTime) + "\n";
	for (auto it : animationContainer)
	{
		output += it.first + "\n";
		for (auto it2 : it.second)
		{
			output += std::to_string(it2.left) + " ";
			output += std::to_string(it2.top) + " ";
			output += std::to_string(it2.width) + " ";
			output += std::to_string(it2.height) + "\n";
		}
	}*/
	return xmlDoc;
}

void AnimatedEntity::loadFromFile(const RessourceManager & ressourceManager)
{
	SpriteEntity::loadFromFile(ressourceManager);
	this->setSwitchAnimationTime(ressourceManager.getData().switchAnimationTime);
	//this->storeAnimation(ressourceManager.getData().animationName);
}

void AnimatedEntity::animationUpdate()
{
	if (currentAnimation != animationContainer.end())
	{
		if (animationClock.getElapsedTime().asMilliseconds() > switchAnimationTime)
		{

			if (textureRectIndex >= currentAnimation->second.size())
			{
				textureRectIndex = 0;
			}
			else
			{
				textureRectIndex++;
			}
			animationClock.restart();
		}

		if (textureRectIndex < currentAnimation->second.size())
		{
			sprite.setTextureRect(currentAnimation->second.at(textureRectIndex));
			setWidthHeight(worldPosition.width, worldPosition.height);
		}
	}
	else
	{
		std::cout << "bad iterator" << std::endl;
	}
}
