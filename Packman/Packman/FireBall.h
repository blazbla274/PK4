#pragma once
#include "Mine.h"
#include "Map.h"

class FireBall :protected virtual Guardian, public Mine
{
public:
	FireBall() = default;
	FireBall(float x, float y, int dir, Map* m);
	~FireBall() = default;
	void update();
	int direction;
	int fireBallRadius{ 7 };
	float velocity{ 6 };
	sf::Vector2f directionVector;
	float explosionTime{ 30 };
	Sprite returnObject();
};

