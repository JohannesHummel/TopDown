#include <SFML/Graphics.hpp>

#include "Framework.h"

int main()
{
	Framework framework;
	framework.run();
}


/*
#define AMOUNTOFVERTICES 4

#include <iostream>
#include <string>
class TileMap : public sf::Drawable, public sf::Transformable
{
public:

	bool load(std::string texture,const int* tiles, int amountOfTiles,int tileSize ,int subtextureSize)
	{
		if (!m_tileset.loadFromFile(texture))
			return false;

		m_vertices.setPrimitiveType(sf::Quads);
		m_vertices.resize(amountOfTiles * amountOfTiles * AMOUNTOFVERTICES);

		for (int i = 0; i < amountOfTiles ; ++i)
			for (unsigned int j = 0; j < amountOfTiles; ++j)
			{
				sf::Vertex* quad = &m_vertices[(i + j * amountOfTiles) * 4];

				// define its 4 corners
				quad[0].position = sf::Vector2f(i * tileSize, j * tileSize);
				quad[1].position = sf::Vector2f((i + 1) * tileSize, j * tileSize);
				quad[2].position = sf::Vector2f((i + 1) * tileSize, (j + 1) * tileSize);
				quad[3].position = sf::Vector2f(i * tileSize, (j + 1) * tileSize);

				//quad->color = sf::Color::Blue;

				quad[0].texCoords = sf::Vector2f(0,0);
				quad[1].texCoords = sf::Vector2f(subtextureSize,0);
				quad[2].texCoords = sf::Vector2f(subtextureSize, subtextureSize);
				quad[3].texCoords = sf::Vector2f(0, subtextureSize);


			}
		return true;
	}


private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// apply the transform
		states.transform *= getTransform();

		// apply the tileset texture
		states.texture = &m_tileset;

		// draw the vertex array
		target.draw(m_vertices, states);
	}

	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
};

int main()
{
	// create the window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Tilemap");

	// define the level with an array of tile indices
	const int level[] =
	{
		1,1,2,
		0,0,0,
		1,0,2
	};


	TileMap tileMap;
	bool c = tileMap.load("images/tileset.png", level, 3, 100,17);

	sf::View v;
	v.setCenter(0, 0);
	v.setSize(1000, 1000);

	//window.setView(v);
	// run the main loop
	while (window.isOpen())
	{
		// handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// draw the map
		window.clear();
		window.draw(tileMap);
		window.display();
	}

	return 0;
}*/



/*

#include <queue>
#include <vector>
#include <cmath>
#include <iostream>

struct AStarNode
{
	unsigned formerCosts = 0;
	unsigned costs = 1;
	unsigned heuristic = 0;
	bool isEnd = false;
	bool isStart = false;
	bool isObstacle = false;
	bool inClosedList =  false;
	bool inOpenList = false;
	int x, y;
	
	AStarNode * formerNode;

	sf::RectangleShape visual;
	AStarNode(int x, int y) : x(x), y(y)
	{
		visual.setSize(sf::Vector2f(50, 50));
		visual.setPosition(x * 50, y * 50);
		visual.setOutlineThickness(1);
		visual.setOutlineColor(sf::Color::Black);
		visual.setFillColor(sf::Color::White);
	}

	void draw(sf::RenderWindow * window)
	{
		if (isEnd)
			visual.setFillColor(sf::Color::Red);
		if (isStart)
			visual.setFillColor(sf::Color::Green);
		if (isObstacle)
			visual.setFillColor(sf::Color::Black);

		window->draw(visual);
	}

	void calucalteHeuristic(int endPosX, int endPosY)
	{
		int distanceX = std::abs(endPosX - x);
		int distanceY = std::abs(endPosY - y);

		heuristic = distanceX + distanceY;
		//std::cout << heuristic << std::endl;
	}

	unsigned getCompleteCosts()
	{
		return formerCosts + costs + heuristic;
	}
};

template <typename comp>
using AStarQueue = std::priority_queue<AStarNode*, std::vector<AStarNode*>, comp>;

AStarNode* nodes[10][10];

auto comperator = [](AStarNode* lhs, AStarNode* rhs)
{
	return lhs->getCompleteCosts() > rhs->getCompleteCosts();
};

AStarQueue<decltype(comperator)> openlist(comperator);


bool checkInsertCondition(int x, int y)
{
	return (x < 10 && x > 0
		&& !nodes[x][y]->inClosedList
		&& !nodes[x][y]->inOpenList
		&& !nodes[x][y]->isObstacle);
}

void putNeighboursInOpenList()
{
	AStarNode* topNode = openlist.top();
	topNode->inOpenList = false;
	openlist.pop();
	int x = topNode->x;
	int y = topNode->y;

	if (checkInsertCondition(x+1, y))
	{
		nodes[x + 1][y]->formerCosts = topNode->getCompleteCosts();
		nodes[x + 1][y]->calucalteHeuristic(9,7);
		nodes[x + 1][y]->formerNode = topNode;
		nodes[x + 1][y]->inOpenList = true;
		openlist.push(nodes[x + 1][y]); 
	}

	if (checkInsertCondition(x, y + 1))
	{
		nodes[x][y + 1]->formerCosts = topNode->getCompleteCosts();
		nodes[x][y + 1]->calucalteHeuristic(9, 7);
		nodes[x][y + 1]->formerNode = topNode;
		nodes[x][y + 1]->inOpenList = true;
		openlist.push(nodes[x][y + 1]);
	}

	if (checkInsertCondition(x - 1, y))
	{
		nodes[x - 1][y]->formerCosts = topNode->getCompleteCosts();
		nodes[x - 1][y]->calucalteHeuristic(9, 7);
		nodes[x - 1][y]->formerNode = topNode;
		nodes[x - 1][y]->inOpenList = true;
		openlist.push(nodes[x - 1][y]);
	}

	if (checkInsertCondition(x, y - 1))
	{
		nodes[x][y - 1]->formerCosts = topNode->getCompleteCosts();
		nodes[x][y - 1]->calucalteHeuristic(9, 7);
		nodes[x][y - 1]->formerNode = topNode;
		nodes[x][y - 1]->inOpenList = true;
		openlist.push(nodes[x][y - 1]);
	}
	topNode->inClosedList = true;
}


void evaluate(AStarNode* node)
{
	if (node != nullptr)
	{
		node->visual.setFillColor(sf::Color::Blue);
		//std::cout << node->x << " " << node->y << std::endl;
		if(!node->isStart)
			evaluate(node->formerNode);
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "ASTAR");

	



	//Build a grid of nodes
	for(int x = 0; x < 10; x++)
		for (int y = 0; y < 10; y++)
		{
			nodes[x][y] = new AStarNode(x, y);
		}


	//set start Node
	nodes[3][4]->isStart = true;
	nodes[3][4]->costs = 0;


	//set end Node
	nodes[9][7]->isEnd = true;

	//insert start NOde in openList
	nodes[3][4]->calucalteHeuristic(9,7);
	nodes[3][4]->inOpenList = true;
	openlist.push(nodes[3][4]);


	//set Obstacles
	nodes[1][1]->isObstacle = true;
	nodes[4][4]->isObstacle = true;
	nodes[5][4]->isObstacle = true;
	nodes[4][5]->isObstacle = true;
	nodes[5][5]->isObstacle = true;
	nodes[6][7]->isObstacle = true;
	nodes[7][7]->isObstacle = true;
	nodes[6][4]->isObstacle = true;
	nodes[2][7]->isObstacle = true;
	nodes[0][7]->isObstacle = true;
	nodes[7][2]->isObstacle = true;
	nodes[7][1]->isObstacle = true;
	nodes[1][1]->isObstacle = true;

	std::cout << "top: " << openlist.top()->x << " " << openlist.top()->y << std::endl;

	//execute A-Star
	while (!openlist.top()->isEnd)
	{
		putNeighboursInOpenList();
		std::cout << "top: " << openlist.top()->x << " " << openlist.top()->y << std::endl;
	}

	evaluate(openlist.top());

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color(128,128,128));

		//render the grid
		for (int x = 0; x < 10; x++)
			for (int y = 0; y < 10; y++)
			{
				nodes[x][y]->draw(&window);
			}
		window.display();
	}

	return 0;
}
*/