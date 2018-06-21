#include "stdafx.h"
#include "FireBall.h"


FireBall::FireBall(float x, float y, int dir, Map* m)
{
	direction = dir; //1-top, 2-right, 3-bottom, 4-left
	map = m;

	texture.loadFromFile("fireBall.png");
	explosion.loadFromFile("explosion.png");


	Guardian::object.setTexture(texture, true);
	Guardian::object.setOrigin(fireBallRadius, fireBallRadius);
	Guardian::object.setPosition(x, y);

	switch (dir) {
	case 1: directionVector = sf::Vector2f{ 0.0f, -1.0f };
		break;
	case 2: directionVector = sf::Vector2f{ 1.0f, 0.0f };
		break;
	case 3: directionVector = sf::Vector2f{ 0.0f, 1.0f };
		break;
	case 4: directionVector = sf::Vector2f{ -1.0f, 0.0f };
		break;
	}
}

void FireBall::update()
{
	
	if (checkCollision(directionVector * velocity)) {

		Guardian::object.move(directionVector * velocity);
		if(Guardian::object.getTexture() != &texture)
			Guardian::object.setTexture(texture);
	}   
	else if (checkCollision(directionVector)) {
		Guardian::object.move(directionVector);
	}
	else if (!explosionMode){
		Guardian::object.setTexture(explosion, true);
		Guardian::object.setOrigin(radiusExposion, radiusExposion);
		explosionMode = true;
	}

	if (explosionMode) {
		explosionTime--;
	}
}

Sprite FireBall::returnObject()
{
	return Guardian::object;
}
