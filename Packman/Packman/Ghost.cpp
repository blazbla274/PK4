#include "stdafx.h"
#include "Ghost.h"


Ghost::Ghost(float x, float y, Map* m, Game* g, Packman* p, int timeToresp)
{
	respX = x;
	respY = y;
	name = "Ghost";
	map = m;
	game = g;
	pacman = p;
	width = 23;
	height = 23;
	texture.loadFromFile("ghostRed.png");
	fearTexture.loadFromFile("ghostFered.png");
	object.setTexture(texture);
	object.setPosition(x, y);
	object.setOrigin(width / 2, height / 2);
	timeToRespawn = timeToresp;
	timeToRespawnSetter = timeToresp;
	velocityHunt = pacman->velocity + pacman->velocity / 3;
	velocity = velocityHunt;
	velocityRunOut = pacman->velocity - pacman->velocity / 2;
}

void Ghost::update()
{
	if (resp) { //respawn moba
		respawn();
		return;
	}
	
	updateVelocity();
	fearDetection();

	int newDirection = bestDirection(); // 1-top, 2-right, 3-bottom, 4-left
	//wybrany kierunek poruszania siê
	bool directChange = false;
	if (movementDirection == sf::Vector2i(0, 1)) { //je¿eli poruszaliœmy siê w dó³ 

		if (checkCollision(velocityVectorLeft) && newDirection == 4) {

			object.move(velocityVectorLeft);
			movementDirection = sf::Vector2i(-1, 0);
		} 
		else if (checkCollision(velocityVectorRight) && newDirection == 2) {

			object.move(velocityVectorRight);
			movementDirection = sf::Vector2i(1, 0);
		}
		else if (checkCollision(velocityVectorBottom)) {

			object.move(velocityVectorBottom);
		} 
		//precyzyjne dojœcie do œciany
		else if (checkCollision(sf::Vector2f(-0.2,0)) && newDirection == 4) {

			object.move(sf::Vector2f(-0.9, 0));
			movementDirection = sf::Vector2i(-1, 0);
		}
		else if (checkCollision(sf::Vector2f(0.2, 0)) && newDirection == 2) {

			object.move(sf::Vector2f(0.9, 0));
			movementDirection = sf::Vector2i(1, 0);
		}
		else if (checkCollision(sf::Vector2f(0, 0.9))) {

			object.move(sf::Vector2f(0, 0.9));
		}
		else
			directChange = true;
	}
	else if (movementDirection == sf::Vector2i(1, 0)) { //je¿eli poruszamu siê prawo

		if (checkCollision(velocityVectorTop) && newDirection == 1) {

			object.move(velocityVectorTop);
			movementDirection = sf::Vector2i(0, -1);
		}
		else if (checkCollision(velocityVectorBottom) && newDirection == 3) {

			object.move(velocityVectorBottom);
			movementDirection = sf::Vector2i(0, 1);
		} else if (checkCollision(velocityVectorRight)) {

			object.move(velocityVectorRight);
		}
		//precyzyjne dojœcie do œciany
		else if (checkCollision(sf::Vector2f(0, -0.9)) && newDirection == 1) {

			object.move(sf::Vector2f(0, -0.9));
			movementDirection = sf::Vector2i(0, -1);
		}
		else if (checkCollision(sf::Vector2f(0, 0.9)) && newDirection == 3) {

			object.move(sf::Vector2f(0, 0.9));
			movementDirection = sf::Vector2i(0, 1);
		}
		else if (checkCollision(sf::Vector2f(0.9, 0))) {

			object.move(sf::Vector2f(0.9, 0));
		}
		else
			directChange = true;
	}
	else if (movementDirection == sf::Vector2i(0, -1)) { //je¿eli poruszamy siê w górê

		if (checkCollision(velocityVectorLeft) && newDirection == 4) {

			object.move(velocityVectorLeft);
			movementDirection = sf::Vector2i(-1, 0);
		}
		else if (checkCollision(velocityVectorRight) && newDirection == 2) {

			object.move(velocityVectorRight);
			movementDirection = sf::Vector2i(1, 0);
		} 
		else if (checkCollision(velocityVectorTop)) {

			object.move(velocityVectorTop);
		}
		//precyzyjne dojœcie do œciany
		else if (checkCollision(sf::Vector2f(-0.9, 0)) && newDirection == 4) {   

			object.move(sf::Vector2f(-0.9, 0));
			movementDirection = sf::Vector2i(-1, 0);
		}
		else if (checkCollision(sf::Vector2f(0.9, 0)) && newDirection == 2) {

			object.move(sf::Vector2f(0.9, 0));
			movementDirection = sf::Vector2i(1, 0);
		}
		else if (checkCollision(sf::Vector2f(0, -0.9))) {

			object.move(sf::Vector2f(0, -0.9));
		}
		else
			directChange = true;
	}
	else if (movementDirection == sf::Vector2i(-1, 0)) { //je¿eli poruszamy siê w lewo

		if (checkCollision(velocityVectorTop) && newDirection == 1) {

			object.move(velocityVectorTop);
			movementDirection = sf::Vector2i(0, -1);
		}
		else if (checkCollision(velocityVectorBottom) && newDirection == 3) {

			object.move(velocityVectorBottom);
			movementDirection = sf::Vector2i(0, 1);
		}
		else if (checkCollision(velocityVectorLeft)) {

			object.move(velocityVectorLeft);
		}
		//precyzyjne dojœcie do œciany 
		else if (checkCollision(sf::Vector2f(0, -0.9)) && newDirection == 1) {

			object.move(sf::Vector2f(0, -0.9));
			movementDirection = sf::Vector2i(0, -1);
		}
		else if (checkCollision(sf::Vector2f(0, 0.9)) && newDirection == 3) {

			object.move(sf::Vector2f(0, 0.9));
			movementDirection = sf::Vector2i(0, 1.0);
		}
		else if (checkCollision(sf::Vector2f(-0.9, 0))) {

			object.move(sf::Vector2f(-0.9, 0));
		}
		else
			directChange = true;
	}
	else  {
		directChange = true;
	}
	
	if (directChange) {

		switch (newDirection) {
		case 1: movementDirection = sf::Vector2i(0,-1);
			break;
		case 2: movementDirection = sf::Vector2i(1, 0);
			break;
		case 3: movementDirection = sf::Vector2i(0, 1);
			break;
		case 4: movementDirection = sf::Vector2i(-1, 0);
			break;
		case 0: movementDirection = sf::Vector2i(0, 0);
			break;
	    }
	}

	colisionDetection();
}

void Ghost::updateVelocity()
{
	if (game->ghostModeRunAway && velocity != velocityRunOut) {

		velocity = velocityRunOut;
	} else if(!game->ghostModeRunAway && velocity != velocityHunt) {

		velocity = velocityHunt;
	}

	velocityVectorLeft = sf::Vector2f(-velocity, 0);
	velocityVectorRight = sf::Vector2f(velocity, 0);
	velocityVectorTop = sf::Vector2f(0, -velocity);
	velocityVectorBottom = sf::Vector2f(0, velocity);
}

int Ghost::bestDirection()
{
	sf::Vector2i sugDirection = sugestedDirection();
	int bestDir = 0; // 1-top, 2-right, 3-bottom, 4-left

	if (sugDirection.y == 0) {
		if (checkCollision(velocityVectorBottom))  bestDir = 3;
		else if (checkCollision(sf::Vector2f(0, 1)))  bestDir = 3;
		else if (checkCollision(velocityVectorTop))  bestDir = 1;
		else if (checkCollision(sf::Vector2f(0, -1)))  bestDir = 1;
	} 
	if (sugDirection.x == 0) {
		if (checkCollision(velocityVectorRight))  bestDir = 2;
		else if (checkCollision(sf::Vector2f(1, 0)))  bestDir = 2;
		else if (checkCollision(velocityVectorLeft))  bestDir = 4;
		else if (checkCollision(sf::Vector2f(-1, 0)))  bestDir = 4;
	}

	if (sugDirection.x > 0) {

		if (checkCollision(velocityVectorRight) && movementDirection != sf::Vector2i(-1,0)) bestDir = 2;
		else if (checkCollision(sf::Vector2f(1, 0)) && movementDirection != sf::Vector2i(-1, 0)) bestDir = 2;
	}
	if (sugDirection.x < 0) {

		if (checkCollision(velocityVectorLeft) && movementDirection != sf::Vector2i(1, 0)) bestDir = 4;
		else if (checkCollision(sf::Vector2f(-1,0)) && movementDirection != sf::Vector2i(1, 0)) bestDir = 4;
	}
	if (sugDirection.y > 0) {

		if (checkCollision(velocityVectorBottom) && movementDirection != sf::Vector2i(0, -1)) bestDir = 3;
		else if (checkCollision(sf::Vector2f(0, 1)) && movementDirection != sf::Vector2i(0, -1)) bestDir = 3;
	}
	if (sugDirection.y < 0) {

		if (checkCollision(velocityVectorTop) && movementDirection != sf::Vector2i(0, 1)) bestDir = 1;
		else if (checkCollision(sf::Vector2f(0, -1)) && movementDirection != sf::Vector2i(0, 1)) bestDir = 1;
	}

	if (bestDir == 0) {

		if (!checkCollision(velocityVectorTop) && !checkCollision(velocityVectorRight) ||
			!checkCollision(sf::Vector2f(0, -1)) && !checkCollision(sf::Vector2f(1, 0))) {

			bestDir = 4;
		} else if (!checkCollision(velocityVectorTop) && !checkCollision(velocityVectorLeft) ||
			!checkCollision(sf::Vector2f(0, -1)) && !checkCollision(sf::Vector2f(-1, 0))) {

			bestDir = 2;
		}
		else if (!checkCollision(velocityVectorBottom) && !checkCollision(velocityVectorLeft) ||
			!checkCollision(sf::Vector2f(0, 1)) && !checkCollision(sf::Vector2f(-1, 0))) {

			bestDir = 2;
		} else if (!checkCollision(velocityVectorBottom) && !checkCollision(velocityVectorRight) ||
			!checkCollision(sf::Vector2f(0, 1)) && !checkCollision(sf::Vector2f(1, 0))) {

			bestDir = 4;
		}
	}

	return bestDir;
}

void Ghost::colisionDetection()
{
	if (pacmanPosition.x + pacman->width - 3 > object.getPosition().x
		&& pacmanPosition.x - pacman->width + 3 < object.getPosition().x
		&& pacmanPosition.y + pacman->height - 3 > object.getPosition().y
		&& pacmanPosition.y - pacman->height + 3 < object.getPosition().y
		) {

		if (game->ghostModeRunAway) {
			game->addPlayerPoint(100);
			capture = true;
		} else
		  	game->gameover = true;
	}
}

void Ghost::fearDetection()
{
	if (game->ghostModeRunAway && object.getTexture() != &fearTexture) {

		object.setTexture(fearTexture);
	}
	else if (!game->ghostModeRunAway && object.getTexture() != &texture) {

		object.setTexture(texture);
	}
}

sf::Vector2i Ghost::sugestedDirection()
{
	sf::Vector2i sdirect(0, 0); //sugestedDirection
	pacmanPosition.x = pacman->pacmanPosition.x;
	pacmanPosition.y = pacman->pacmanPosition.y;
	gohstPosition.x = object.getPosition().x;
	gohstPosition.y = object.getPosition().y;

	if (pacmanPosition.x > gohstPosition.x) {
		sdirect.x = 1;
	}
	else if (pacmanPosition.x != gohstPosition.x) {

		sdirect.x = -1;
	}

	if (pacmanPosition.y > gohstPosition.y) {

		sdirect.y = 1;
	}
	else if (pacmanPosition.y != gohstPosition.y) {

		sdirect.y = -1;
	}
	if (game->ghostModeRunAway)
		return -sdirect;
	else
		return sdirect;
}

void Ghost::respawn()
{
	if (--timeToRespawn <= 0) {

		object.move(sf::Vector2f(0, -1));
		if (object.getPosition().y <= 167.2) {
			resp = false;
		}
	}
}

void Ghost::reset()
{
	timeToRespawn = timeToRespawnSetter;
	resp = true;
	object.setPosition(respX,respY);
	object.setTexture(texture);
	movementDirection = sf::Vector2i(0, 0);
	capture = false;
	game->ghostModeRunAway = false;
	game->bonusAbilityEatTimer = 0;
	game->bonusSpeed = 0;
	game->bonusSpeedTimer = 0;
	game->bonusMultipler = 1;
	game->bonusMultiplerTimer = 0;
}

void Ghost::resetControler(int x)
{
	if (++resetCounter > x) {
		bool ghostMode = game->ghostModeRunAway;
		int eatTimer = game->bonusAbilityEatTimer;
		reset();
		game->ghostModeRunAway = ghostMode;
		game->bonusAbilityEatTimer = eatTimer;
		resetCounter = 0;
	}
}

void Ghost::draw(RenderTarget & target, RenderStates state) const
{
	target.draw(this->object, state);
}
