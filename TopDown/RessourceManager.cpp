#include "RessourceManager.h"

using namespace tinyxml2;


RessourceManager::RessourceManager()
{
}


RessourceManager::~RessourceManager()
{
}


void RessourceManager::readFromFile(std::string const &filename)
{
	/*
	std::string line;
	std::ifstream file(filename);
	int count = 0;


	if (file.is_open())
	{
		std::string startLine;
		while (std::getline(file, line))
		{
			std::stringstream lineStream(line);
			std::string tempString;


			lineStream >> tempString;
			//one digit stream
			std::stringstream tagStream(tempString);
			float digit = 0;
			//multiple digits stream
			std::stringstream intStream(line);
			int digitIterator = 0;

			/*		switch (count)
			{
			case 0:
			data.objectType = tempString;
			std::cout << data.objectType << std::endl;
			break;

			case 1:
			data.tag = tempString;
			std::cout << data.tag << std::endl;
			break;

			case 2:
			tagStream >> digit;
			data.hasPosition = digit;
			std::cout << data.hasPosition << std::endl;
			break;

			case 3:
			while (intStream >> digit)
			{
			data.position[digitIterator] = digit;
			std::cout << data.position[digitIterator] << std::endl;
			}
			digitIterator++;
			break;

			case 4:
			tagStream >> digit;
			data.hasPositionInTiledMap = digit;
			std::cout << data.hasPositionInTiledMap << std::endl;
			break;

			case 5:
			while (intStream >> digit)
			{
			data.positionInTiledMap[digitIterator] = digit;
			std::cout << data.positionInTiledMap[digitIterator] << std::endl;
			}
			digitIterator++;
			break;

			case 6:
			tagStream >> digit;
			data.hasTexture = digit;
			std::cout << data.hasTexture << std::endl;
			break;

			case 7:
			data.textureName = line;
			std::cout << data.textureName << std::endl;
			break;

			case 8:
			tagStream >> digit;
			data.hasAnimation = digit;
			std::cout << data.hasAnimation << std::endl;
			break;

			case 9:
			tagStream >> digit;
			data.amountOfAnimations = digit;
			std::cout << data.amountOfAnimations << std::endl;
			break;

			case 10:
			while (intStream >> digit)
			{
			data.defaultSprite.push_back(digit);
			}
			for (auto const& c : data.defaultSprite)
			std::cout << c << ' ';
			digitIterator++;
			break;
			default:
			break;
			}
			if (count == 0)
			{
				startLine = line;
			}

			if (startLine == "BaseEntity")
			{
				readBaseEntity(count, tempString, tagStream, digit, intStream, digitIterator);
			}
			if (startLine == "SpriteEntity")
				readSpriteEntity(count, tempString, tagStream, digit, intStream, digitIterator);
			if (startLine == "AnimatedEntity")
				readAnimatedEntity(count, tempString, tagStream, digit, intStream, digitIterator);
			if (startLine == "TiledEntity")
				readTiledEntity(count, tempString, tagStream, digit, intStream, digitIterator);
			count++;
		}
		file.close();
	}*/

	XMLDocument xmlDoc;
	xmlDoc.LoadFile(filename.c_str());

	XMLNode * pRoot = xmlDoc.FirstChild();
	XMLElement * pElement = pRoot->FirstChildElement("ObjectType");
	data.objectType = pElement->GetText();

	if (data.objectType == "BaseEntity")
	{
		readBaseEntity(filename);
	}
	if (data.objectType == "SpriteEntity")
	{
		readSpriteEntity(filename);
	}
	if (data.objectType == "AnimatedEntity")
	{
		readAnimatedEntity(filename);
	}
	if (data.objectType == "TiledEntity")
	{
		readTiledEntity(filename);
	}
}

void RessourceManager::writeInFile(std::string const & filename, BaseEntityExp  &baseEntity)
{
	baseEntity.saveToFile()->SaveFile(filename.c_str());

	/*std::ofstream file(filename);
	if (file.is_open())
	{
	file << baseEntity.saveToFile();
	file.close();
	}*/
}

void RessourceManager::readBaseEntity(const std::string & filename)
{
	XMLDocument xmlDoc;
	xmlDoc.LoadFile(filename.c_str());

	XMLNode * pRoot = xmlDoc.FirstChild();
	XMLElement * pElement = pRoot->FirstChildElement("ObjectType");
	data.objectType = pElement->GetText();

	pElement = pRoot->FirstChildElement("RenderPosition");
    pElement->QueryIntText(&data.renderPos);

	pElement = pRoot->FirstChildElement("Tag");
	data.tag = pElement->GetText();

	/*
	switch (count)
	{
	case 0:
	data.objectType = tempString;
	std::cout << data.objectType << std::endl;
	break;
	case 1:
	tagStream >> digit;
	data.renderPos = digit;
	std::cout << data.renderPos << std::endl;
	break;
	case 2:
	data.tag = tempString;
	std::cout << data.tag << std::endl;
	break;
	default:
	break;
	}*/
}

void RessourceManager::readSpriteEntity(const std::string & filename)
{
	readBaseEntity(filename);

	XMLDocument xmlDoc;
	xmlDoc.LoadFile(filename.c_str());

	XMLNode * pRoot = xmlDoc.FirstChild();
	XMLElement * pElement = pRoot->FirstChildElement("worldPosition");
	pElement->QueryIntAttribute("x", &data.position[0]);
	pElement->QueryIntAttribute("y", &data.position[1]);


	pElement = pRoot->FirstChildElement("size");
	pElement->QueryIntAttribute("width", &data.size[0]);
	pElement->QueryIntAttribute("height", &data.size[1]);

	pElement = pRoot->FirstChildElement("textureName");
	data.textureName = pElement->GetText();



	/*
	readBaseEntity(count, tempString, tagStream, digit, intStream, digitIterator);

	switch (count)
	{
	case 3:
	while (intStream >> digit)
	{
	data.position[digitIterator] = digit;
	std::cout << data.position[digitIterator] << std::endl;
	}
	digitIterator++;
	break;
	case 4:
	while (intStream >> digit)
	{
	data.size[digitIterator] = digit;
	std::cout << data.size[digitIterator] << std::endl;
	}
	digitIterator++;
	break;
	case 5:
	data.textureName = tempString;
	std::cout << data.textureName << std::endl;
	break;
	default:
	break;
	}
	*/
}

void RessourceManager::readAnimatedEntity(const std::string & filename)
{
	readSpriteEntity(filename);

	XMLDocument xmlDoc;
	xmlDoc.LoadFile(filename.c_str());

	XMLNode * pRoot = xmlDoc.FirstChild();

	XMLElement * pElement = pRoot->FirstChildElement("switchAnimationTime");
	pElement->QueryFloatText(&data.switchAnimationTime);


	pElement = pRoot->FirstChildElement("Animations");
	XMLElement * pListElement = pElement->FirstChildElement("Item");
	while (pListElement != nullptr)
	{
		int iOutListValue;
		pListElement->QueryIntText(&iOutListValue);
		data.subTextures.push_back(iOutListValue);
		pListElement = pListElement->NextSiblingElement("Item");
	}




	/*
	switch (count)
	{
	case 6:
		tagStream >> digit;
		data.switchAnimationTime = digit;
		std::cout << data.switchAnimationTime << std::endl;
		break;
	case 7:
		data.animationName = tempString;
		std::cout << data.animationName << std::endl;
		break;
	case 8:
		while (intStream >> digit)
		{
			data.animationRect.push_back(digit);
		}
		for (auto const& c : data.animationRect)
			std::cout << c << ' ';
		digitIterator++;
		break;
	default:
		break;
	}*/
}

void RessourceManager::readTiledEntity(const std::string &filename)
{
	readBaseEntity(filename);

	XMLDocument xmlDoc;
	xmlDoc.LoadFile(filename.c_str());

	XMLNode * pRoot = xmlDoc.FirstChild();
	XMLElement * pElement = pRoot->FirstChildElement("tiledMapArea");
	pElement->QueryIntAttribute("left", &data.tileMapArea.left);
	pElement->QueryIntAttribute("top", &data.tileMapArea.top);
	pElement->QueryIntAttribute("width", &data.tileMapArea.width);
	pElement->QueryIntAttribute("height", &data.tileMapArea.height);


	pElement = pRoot->FirstChildElement("subTextures");
	XMLElement * pListElement = pElement->FirstChildElement("Item");
	while (pListElement != nullptr)
	{
		int iOutListValue;
		pListElement->QueryIntText(&iOutListValue);
		data.subTextures.push_back(iOutListValue);
		pListElement = pListElement->NextSiblingElement("Item");
	}

/*
	switch (count)
	{
	case 3:
		while (intStream >> digit)
		{
			data.tileMapArea.push_back(digit);
		}
		for (auto const& c : data.tileMapArea)
			std::cout << c << ' ';
		std::cout << std::endl;
		digitIterator++;
		break;
	case 4:
		while (intStream >> digit)
		{
			data.subTextures.push_back(digit);
		}
		for (auto const& c : data.subTextures)
			std::cout << c << ' ';
		digitIterator++;
		break;
	default:
		break;
	}*/
}


 DataType RessourceManager::getData() const
{
	return data;
}

