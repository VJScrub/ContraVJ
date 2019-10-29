#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "SpreadGun.h"

void SpreadGun::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/sp.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1, 1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);


	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));

	sprite->changeAnimation(0);

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x), float(tileMapDispl.y)));
	final = false;
}

void SpreadGun::update(int deltaTime)
{
	sprite->update(deltaTime);
}

void SpreadGun::render()
{
	if (!final)
		sprite->render();
}

void SpreadGun::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

bool SpreadGun::hurted(float x, float y)
{
	if ((x < (posIni.x + 32) && x > posIni.x) && (y > posIni.y && y < posIni.y + 32))
	{
		return true;
	}
	else
		return false;
}

void SpreadGun::setPosition(const glm::vec2& pos)
{
	posIni = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posIni.x), float(tileMapDispl.y + posIni.y)));

}

void SpreadGun::setfinal() {
	final = true;
}