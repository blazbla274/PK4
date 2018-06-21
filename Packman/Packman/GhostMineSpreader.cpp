#include "stdafx.h"
#include "GhostMineSpreader.h"


GhostMineSpreader::GhostMineSpreader(float x, float y, Map* m, Game* g, Packman* p)
{
	respX = x;
	respY = y;
	name = "Ghost";
	map = m;
	game = g;
	pacman = p;
	width = 23;
	height = 23;
	texture.loadFromFile("ghostBrown.png");
	fearTexture.loadFromFile("ghostFered.png");
	object.setTexture(texture);
	object.setPosition(x, y);
	object.setOrigin(width / 2, height / 2);
	timeToRespawn = 70;
	timeToRespawnSetter = 70;

	velocityHunt = pacman->velocity - pacman->velocity / 3;
	velocity = velocityHunt;
	velocityRunOut = pacman->velocity - pacman->velocity / 1.5;
	srand(time(NULL));
}

void GhostMineSpreader::update()
{
	if (resp) { //respawn moba
		GhostMineSpreader::respawn();
		return;
	}

	updatePacmanPosition();
	updateVelocity();
	fearDetection();
	inspectMine();

	if (--dropCounter < 0 && !game->ghostModeRunAway) {
		dropCounter = dropcooldown;
		dropMine();
	}

	while (!makeMove()) {
		direction = (std::rand() % 4) + 1;
	}
	colisionDetection();
}

bool GhostMineSpreader::makeMove()
{
	if (direction == 4) {

		if (checkCollision(velocityVectorLeft)) {

			object.move(velocityVectorLeft);
		}
		else if (checkCollision(sf::Vector2f(-1.6, 0))) {

			object.move(sf::Vector2f(-1, 0));
		}
		else return false;
	}
	else if (direction == 2) {

		if (checkCollision(velocityVectorRight)) {

			object.move(velocityVectorRight);
		}
		else if (checkCollision(sf::Vector2f(1.6, 0))) {

			object.move(sf::Vector2f(1, 0));
		}
		else return false;
	}
	else if (direction == 1) {

		if (checkCollision(velocityVectorTop)) {

			object.move(velocityVectorTop);
		}
		else if (checkCollision(sf::Vector2f(0, -1.6))) {

			object.move(sf::Vector2f(0, -1));
		}
		else return false;
	}
	else if (direction == 3) {

		if (checkCollision(velocityVectorBottom)) {

			object.move(velocityVectorBottom);
		}
		else if (checkCollision(sf::Vector2f(0, 1.6))) {

			object.move(sf::Vector2f(0, 1));
		}
		else return false;
	}

	return true;
}

void GhostMineSpreader::exposionDetection(Mine& it)
{
	if (pacmanPosition.x + pacman->width  > it.object.getPosition().x
		&& pacmanPosition.x - pacman->width  < it.object.getPosition().x
		&& pacmanPosition.y + pacman->height  > it.object.getPosition().y
		&& pacmanPosition.y - pacman->height  < it.object.getPosition().y
		) {

		game->gameover = true;
	}
}

void GhostMineSpreader::updatePacmanPosition()
{
	pacmanPosition.x = pacman->pacmanPosition.x;
	pacmanPosition.y = pacman->pacmanPosition.y;
}

void GhostMineSpreader::respawn()
{
	if (--timeToRespawn <= 0) {

		object.move(sf::Vector2f(0, 1));
		if (object.getPosition().y >= 263.6) {
			resp = false;
		}
	}
}

void GhostMineSpreader::dropMine()
{
	Mine mina(object.getPosition().x, object.getPosition().y);
	mineList.push_back(mina);
}

void GhostMineSpreader::inspectMine()
{
	for (auto itMine = mineList.begin(); itMine != mineList.end(); ++itMine) { 

		if (itMine->timeCounter < 0) {
			mineList.erase(itMine);
			break;
		}
		itMine->update();
		if(itMine->explosionMode)
			exposionDetection(*itMine);			
	}
}

void GhostMineSpreader::draw(RenderTarget & target, RenderStates state) const
{
	for (auto itMine = mineList.begin(); itMine != mineList.end(); ++itMine) {
		if (itMine->timeCounter > 0.2 * itMine->time) {

			target.draw(itMine->object, state);
			target.draw(itMine->line1, state);
			target.draw(itMine->line2, state);
			target.draw(itMine->line3, state);
			target.draw(itMine->line4, state);
		} else {

			target.draw(itMine->object, state);
		}
		
	}

	if(!this->capture)
		target.draw(this->object, state);
}
