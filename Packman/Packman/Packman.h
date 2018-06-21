#pragma once
#include <SFML/Graphics.hpp>
#include "Guardian.h"
#include "Map.h"

using namespace sf;

class Packman :public sf::Drawable, protected virtual Guardian
{
public:
	friend class Ghost;
	friend class GhostMineSpreader;
	friend class GhostFireShooter;
	Packman(float x, float y, Map *mapa, Game *gra);
	Packman() = delete;
	~Packman() = default;
	void update();
	void updateVelocity();
	void makeMove(int direction);
	int lastMovment{ 1 };
	sf::Vector2f pacmanPosition;
private:
	const float velocity{ 2.0f };
	Vector2f velocityVectorLeft;
	Vector2f velocityVectorRight;
	Vector2f velocityVectorTop;
	Vector2f velocityVectorBottom;
	void draw(RenderTarget& target, RenderStates state) const override;
};

