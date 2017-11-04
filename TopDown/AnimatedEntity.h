#pragma once
#include "SpriteEntity.h"
#include "tinyxml2.h"

class AnimatedEntity : public SpriteEntity
{
public:
	AnimatedEntity();
	~AnimatedEntity();

	void masterUpdate(float deltaTime);

	void setSwitchAnimationTime(float switchAnimationTime);
	void setDefault(sf::IntRect rect);
	void storeAnimation(std::string key, std::vector<sf::IntRect> animations);
	void applyAnimation(std::string key);

	virtual tinyxml2::XMLDocument* saveToFile();
	virtual void loadFromFile(const RessourceManager & ressourceManager);

protected:
	
private:
	sf::Clock animationClock;
	float switchAnimationTime;
	float currentTime;
	int textureRectIndex;

	std::map<std::string, std::vector<sf::IntRect>> animationContainer;
	std::map<std::string, std::vector<sf::IntRect>>::iterator currentAnimation;

	void animationUpdate();

};

