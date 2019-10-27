#include "PantallaLeve2Boss.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"

void PantallaLeve2Boss::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	NextLevel = false;
	mostrar = true;
	delayNextLevel = 50;
	spritesheet.loadFromFile("images/Level2Jefe.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(512, 512), glm::vec2(0.5, 0.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);
	
	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(0, glm::vec2(0.5f, 0.f));
	sprite->addKeyframe(0, glm::vec2(0.f, 0.5f));
	sprite->addKeyframe(0, glm::vec2(0.5f, 0.f));

	sprite->changeAnimation(0);

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x), float(tileMapDispl.y)));

}

void PantallaLeve2Boss::update(int deltaTime)
{
	sprite->update(deltaTime);
}

void PantallaLeve2Boss::render()
{
	sprite->render();
}

void PantallaLeve2Boss::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

int PantallaLeve2Boss::getAnimation()
{
	return 0;
}
