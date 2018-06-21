#pragma once
#include <SFML/Graphics.hpp>
#include "Point.h"
#include <list>
#include "Bonus.h"

using namespace sf;
using namespace std;

class Map :public sf::Drawable
{
public:
	Map(Game* g);
	~Map() = default;
	friend class Guardian;
private:
	Game * game;
	const int mapSizeX{ 64 };
	const int mapSizeY{ 48 };
	const int squerSize{ 12 };
	int wallMap[48][64];
	list<Point> pointList;
	mutable list<Point>::const_iterator itPoint;
	list<Bonus*> bonusList;
	mutable list<Bonus*>::const_iterator itBonus;

	Texture wallTexture, emptyTexture;
	void draw(RenderTarget& target, RenderStates state) const override;
	void addPoint(float x, float y);
	void addBonus(float x, float y, int);
	void loadMap();
};