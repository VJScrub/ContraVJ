#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "EnemyStage3.h"

void EnemyStage3::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	muerto = false;
	spritesheet.loadFromFile("images/EnemyStage3.png", TEXTURE_PIXEL_FORMAT_RGBA);
	// crear Sprite(quadSize, sizeInSpritesheet, spritesheet, program);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.5, 0.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(0, glm::vec2(0.5f, 0.f));
	sprite->addKeyframe(0, glm::vec2(0.f, 0.5f));

	sprite->setAnimationSpeed(1, 8);
	sprite->addKeyframe(1, glm::vec2(0.5f, 0.5f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));


	spritesheetMuerto.loadFromFile("images/muerteEnemigo.png", TEXTURE_PIXEL_FORMAT_RGBA);
	// crear Sprite(quadSize, sizeInSpritesheet, spritesheet, program);
	spriteMuerto = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.5, 0.5), &spritesheetMuerto, &shaderProgram);
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

void EnemyStage3::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (muerto == true)
	{
		if (sprite->animation() != 1)
			sprite->changeAnimation(1);

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

void EnemyStage3::render()
{
	
	sprite->render();
	if (muerto == true)
		spriteMuerto->render();
}

void EnemyStage3::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void EnemyStage3::setPosition(const glm::vec2& pos)
{
	posEnemy = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

int EnemyStage3::getPositionX()
{
	return posEnemy.x;
}

int EnemyStage3::getPositionY()
{
	return posEnemy.y;
}

bool EnemyStage3::hurted(float x, float y)
{
	if ((x < (posEnemy.x + 32) && x > posEnemy.x) && (y > posEnemy.y&& y < posEnemy.y + 32))
	{
		return true;
	}
	else
		return false;
}

void EnemyStage3::muerteEnemyPersona()
{
	muerto = true;

}

bool EnemyStage3::final()
{
	return fin;
}

int EnemyStage3::getVidas()
{
	return vidas;
}

void EnemyStage3::setVidas(int _vida)
{
	vidas = _vida;
}
