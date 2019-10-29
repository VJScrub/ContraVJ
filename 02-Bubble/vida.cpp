#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "vida.h"
#include "Game.h"

void vida::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/vidas.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1, 1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite->changeAnimation(0);

	tileMapDispl = tileMapPos;
	
	mostrar = true;
}

void vida::update(int deltaTime)
{
	sprite->update(deltaTime);
}

void vida::render()
{
	if (mostrar)
		sprite->render();
}

void vida::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void vida::setPosition(const glm::vec2& pos)
{
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posIni.x), float(tileMapDispl.y + posIni.y)));
}

bool vida::getMostrar()
{
	return mostrar;
}

void vida::setMostrar(bool _mostrar)
{
	mostrar = _mostrar;
}
