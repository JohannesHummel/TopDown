#include "Framework.h"
#include "player.h"
#include "Obstacle.h"
//#include "AnimatedEntity.h"
#include <SFML/Graphics.hpp>

#include "TextureManager.h"


#include"AnimatedEntityTest.h"
#include "TiledEntityTest.h"

#include "TileMap.h"

Framework::Framework()
{
	initializeWindow();
}


Framework::~Framework()
{
	delete window;
	window = nullptr;
}

void Framework::run()
{
	TextureManager textureManager;
	textureManager.loadTexture("images/dragonAnim.png", "dragon");
	textureManager.loadTexture("images/bild.jpg", "stone");
	textureManager.loadTexture("images/tileset.png", "tileset");
	EntityManager entityManager(*window);
	std::shared_ptr<Player> p1(std::make_shared<Player>(*textureManager.getTexture("dragon"), sf::Vector2f(1, 1),&entityManager));
	p1->setRenderPos(2);
	std::shared_ptr<Obstacle> p2(std::make_shared<Obstacle>(*textureManager.getTexture("stone"), sf::Vector2f(3, 3), &entityManager));
	p2->setRenderPos(1);

	p2->setPosition(sf::Vector2f(100, 100));

	std::shared_ptr<AnimatedEntityTest> aet(std::make_shared<AnimatedEntityTest>());
	aet->setRenderPos(1);
	aet->setTag("AET");
	aet->setTexture(*textureManager.getTexture("dragon"));
	aet->setEntityManager(&entityManager);


	std::vector<sf::IntRect> walkDown;
	walkDown.push_back(sf::IntRect(0, 0, 100, 100));
	walkDown.push_back(sf::IntRect(0, 0, 100, 100));
	walkDown.push_back(sf::IntRect(200, 0, 100, 100));
	aet->storeAnimation("walkDown", walkDown);
	aet->setDefault(sf::IntRect(0, 0, 100, 100));
	aet->setSwitchAnimationTime(200);
	aet->setPosition(100, 100);
	aet->setWidthHeight(200, 200);
	entityManager.insertEntity(aet);
	//entityManager.insertEntity(p1);
	//entityManager.insertEntity(p2);



	std::vector<sf::IntRect> subtexrects;
	subtexrects.push_back(sf::IntRect(0,0,17,17));
	subtexrects.push_back(sf::IntRect(17, 0,17,17));
	subtexrects.push_back(sf::IntRect(0, 0,17,17));
	subtexrects.push_back(sf::IntRect(34, 34,17,17));
	subtexrects.push_back(sf::IntRect(0, 0,17,17));
	subtexrects.push_back(sf::IntRect(34, 17,17,17));
	//subtexrects.push_back(sf::IntRect(0, 0,17,17));
	//subtexrects.push_back(sf::IntRect(0, 0,17,17));
	//subtexrects.push_back(sf::IntRect(0, 0,17,17));

	TileMap tilemap(*textureManager.getTexture("tileset"),sf::Vector2u(3,2),200, subtexrects);
	entityManager.setTileMap(&tilemap);

	std::shared_ptr<TiledEntityTest> tet(std::make_shared<TiledEntityTest>());
	tet->setEntityManager(&entityManager);
	tet->setTag("TET");
	tet->setTileMapArea(sf::IntRect(0, 0, 1, 2));
	std::vector<std::vector<sf::IntRect>> subTextures;
	std::vector<sf::IntRect> v1;
	v1.push_back(sf::IntRect(17, 17, 17, 17));
	v1.push_back(sf::IntRect(17, 17, 17, 17));
	subTextures.push_back(v1);
	//subTextures.push_back(v1);
	tet->setSubTextures(subTextures);

	entityManager.insertEntity(tet);

	float oldTime = 0;
	float newTime = 0;
	float deltaTime;
	sf::Clock clock;

	sf::View view1;
	view1.reset(sf::FloatRect(0, 0, 800, 600));
	view1.setRotation(0);
	window->setView(view1);

	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
			}
		
			if (event.type == sf::Event::Resized)
			{

			}
				
		}

		oldTime = newTime;
		newTime = clock.getElapsedTime().asMilliseconds();
		deltaTime = newTime - oldTime;
		
		window->clear();
		entityManager.update(deltaTime);
		window->draw(tilemap);
		entityManager.render();
		window->display();
	}
}

void Framework::initializeWindow()
{
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "SFML works!", sf::Style::Default);
}