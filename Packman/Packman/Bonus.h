#pragma once
class Bonus
{
public:
	Bonus() = default;
	~Bonus() = default;
	friend class Map;
	Sprite object;
	Texture texture;
	Game* game;
	int width;
	int height;
	int origin;
	float posX, posY;
	virtual void action() = 0;
};