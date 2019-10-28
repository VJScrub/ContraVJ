#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Boss.h"

enum Dir {
	RIGHT, LEFT
};

void Boss::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	muerto = false;
	spritesheet.loadFromFile("images/Boss.png", TEXTURE_PIXEL_FORMAT_RGBA);
	// crear Sprite(quadSize, sizeInSpritesheet, spritesheet, program);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(1, 1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));


	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));


	spritesheetMuerto.loadFromFile("images/muerteEnemigo.png", TEXTURE_PIXEL_FORMAT_RGBA);
	// crear Sprite(quadSize, sizeInSpritesheet, spritesheet, program);
	spriteMuerto = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.5, 0.5), &spritesheetMuerto, &shaderProgram);
	spriteMuerto->setNumberAnimations(3);

	spriteMuerto->setAnimationSpeed(0, 8);
	spriteMuerto->addKeyframe(0, glm::vec2(0.f, 0.f));

	spriteMuerto->setAnimationSpeed(1, 8);
	spriteMuerto->addKeyframe(0, glm::vec2(0.f, 0.f));
	spriteMuerto->addKeyframe(1, glm::vec2(0.f, 0.5f));

	spriteMuerto->setAnimationSpeed(2, 8);
	spriteMuerto->addKeyframe(0, glm::vec2(0.f, 0.f));
	spriteMuerto->addKeyframe(1, glm::vec2(0.f, 0.5f));
	spriteMuerto->addKeyframe(2, glm::vec2(0.5, 0.f));

	spriteMuerto->changeAnimation(0);
	spriteMuerto->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));

	DelayMuerte = 8;
	fin = false;
	vidas = 1;
	mostrar = false;
	direccion = RIGHT;
}

void Boss::update(int deltaTime)
{

	sprite->update(deltaTime);
	if (muerto == true)
	{
		if (spriteMuerto->animation() == 0 && DelayMuerte == 0) {
			DelayMuerte = 8;
			spriteMuerto->changeAnimation(1);
		}
		else if (spriteMuerto->animation() == 1 && DelayMuerte == 0) {
			DelayMuerte = 8;
			spriteMuerto->changeAnimation(2);
		}
		else if (spriteMuerto->animation() == 2 && DelayMuerte == 0)
			fin = true;
		else
			DelayMuerte -= 1;
		spriteMuerto->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));

	}

	if (mostrar) {
		if (direccion == RIGHT) {
			if (posEnemy.x < 19 * map->getTileSize())
				posEnemy.x += 1;
			else
				direccion = LEFT;
		}
		else {
			if (posEnemy.x > 8.5 * map->getTileSize())
				posEnemy.x -= 1;
			else
				direccion = RIGHT;
		}
	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));


}

void Boss::render()
{
	if (muerto == true)
		spriteMuerto->render();
	else
	{
		if (mostrar)
			sprite->render();
	}
}

void Boss::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Boss::setPosition(const glm::vec2& pos)
{
	posEnemy = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

int Boss::getPositionX()
{
	return posEnemy.x;
}

int Boss::getPositionY()
{
	return posEnemy.y;
}

bool Boss::hurted(float x, float y)
{
	if ((x < (posEnemy.x + 32) && x > posEnemy.x) && (y > posEnemy.y&& y < posEnemy.y + 32))
	{
		return true;
	}
	else
		return false;
}

void Boss::muerteEnemyPersona()
{
	muerto = true;
}

bool Boss::final()
{
	return fin;
}

int Boss::getVidas()
{
	return vidas;
}

void Boss::setVidas(int _vida)
{
	vidas = _vida;
}

void Boss::setMostrar(int _mostrar)
{
	mostrar = _mostrar;
}

bool Boss::getMostrar() {
	return mostrar;
}