#include "stdafx.h"
#include "Map.h"
#include <fstream>
#include <math.h>

using namespace sf;
using namespace std;

Map::Map(Game* g)
{
	game = g;
	wallTexture.loadFromFile("wallTexture.png"); 
	emptyTexture.loadFromFile("emptyTexture.png");

	loadMap();
}

void Map::draw(RenderTarget & target, RenderStates state) const
{
	vector <int> coordinate;
	Sprite field;

	for (int i = 0; i < mapSizeY; i++) { //rysowanie mapy
		for (int j = 0; j < mapSizeX; j++) {

			coordinate.clear();
			coordinate.push_back((float)i*squerSize);
			coordinate.push_back((float)j*squerSize);
			field.setPosition(sf::Vector2f(coordinate[1], coordinate[0]));
			if (wallMap[i][j] == 1) {

				field.setTexture(wallTexture);
			} else {

				field.setTexture(emptyTexture);
			}
			target.draw(field, state);
		}
	}

	for (itPoint = pointList.begin(); itPoint != pointList.end(); ++itPoint) {//rysowanie punktów

		target.draw(itPoint->object, state);
	}
	Bonus* bonWsk;
	for (itBonus = bonusList.begin(); itBonus != bonusList.end(); ++itBonus) { //rysowanie punktów

		bonWsk = *itBonus;
		target.draw(bonWsk->object, state);
	}
}

void Map::addPoint(float x, float y)
{
	Point newPoint(x, y);

	pointList.push_back(newPoint);
}

void Map::addBonus(float x, float y, int type) //type okreœla jaki bonus
{
	Bonus *bonusWsk = nullptr;
	switch (type) {
	case 1: bonusWsk = new BonusSpeed(x, y, game);
		break;
	case 2: bonusWsk = new BonusMultipler(x, y, game);
		break;
	case 3: bonusWsk = new BonusAbilityEat(x, y, game);
		break;
	}
	if(bonusWsk != nullptr)
		bonusList.push_back(bonusWsk);
}

void Map::loadMap()
{
	fstream map, pointMap, bonusMap;
	map.open("map.txt", ios::in);
	pointMap.open("pointMap.txt", ios::in);
	bonusMap.open("bonusMap.txt", ios::in);

	if (map.good() == false || pointMap.good() == false || bonusMap.good() == false) { //oznacza ze plik nie istnieje 

		cout << "W katalogu z programem musi znalezæ siê plik base.blaut" << endl;
		for (int i = 0; i < mapSizeY; i++) {
			for (int j = 0; j < mapSizeX; j++) {
				wallMap[i][j] = 1;
			}
		}
	}
	else {

		string mapLine;
		string mapPoint;
		string mapBonus;

		for (int i = 0; i < mapSizeY; i++) {
			getline(map, mapLine);
			getline(pointMap, mapPoint);
			getline(bonusMap, mapBonus);
			for (int j = 0; j < mapSizeX; j++) {
				wallMap[i][j] = mapLine[j] - 48;
				if ((mapPoint[j] - 48) == 1) {
					addPoint(squerSize*j, squerSize*i);
				}
				if ((mapBonus[j] - 48) == 1) {
					addBonus(squerSize*j, squerSize*i, 1);
				}
				else if ((mapBonus[j] - 48) == 2) {
					addBonus(squerSize*j, squerSize*i, 2);
				}
				else if ((mapBonus[j] - 48) == 3) {
					addBonus(squerSize*j, squerSize*i, 3);
				}
			}
		}
		map.close();
		pointMap.close();
		bonusMap.close();
	}
}

