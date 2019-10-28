#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "EnemyStage2Key.h"

void EnemyStage2Key::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	muerto = false;
	spritesheet.loadFromFile("images/EnemyStage2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	// crear Sprite(quadSize, sizeInSpritesheet, spritesheet, program);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.5, 0.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(0, glm::vec2(0.5f, 0.f));
	sprite->addKeyframe(0, glm::vec2(0.f, 0.5f));
	sprite->addKeyframe(0, glm::vec2(0.5f, 0.5f));


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
}

void EnemyStage2Key::update(int deltaTime)
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
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));

	
}

void EnemyStage2Key::render()
{
	if (muerto == true)
		spriteMuerto->render();
	else
		sprite->render();
}

void EnemyStage2Key::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void EnemyStage2Key::setPosition(const glm::vec2& pos)
{
	posEnemy = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

int EnemyStage2Key::getPositionX()
{
	return posEnemy.x;
}

int EnemyStage2Key::getPositionY()
{
	return posEnemy.y;
}

bool EnemyStage2Key::hurted(float x, float y)
{
	if ((x < (posEnemy.x + 32) && x > posEnemy.x) && (y > posEnemy.y&& y < posEnemy.y + 32))
	{
		return true;
	}
	else
		return false;
}

void EnemyStage2Key::muerteEnemyPersona()
{
	muerto = true;
}

bool EnemyStage2Key::final()
{
	return fin;
}

int EnemyStage2Key::getVidas()
{
	return vidas;
}

void EnemyStage2Key::setVidas(int _vida)
{
	vidas = _vida;
}
