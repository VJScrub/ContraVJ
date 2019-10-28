#include "PantallaLevel2Stage1.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"

void PantallaLevel2Stage1::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	NextLevel = false;
	mostrar = true;
	delayNextLevel = 50;
	spritesheet.loadFromFile("images/Level2Puerta.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(512, 512), glm::vec2(0.5, 0.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);


	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(0, glm::vec2(0.5f, 0.f));

	sprite->changeAnimation(0);

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x), float(tileMapDispl.y)));
	
	
	spritesheetFIN.loadFromFile("images/Level2Rebentado.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteFIN = Sprite::createSprite(glm::ivec2(512, 512), glm::vec2(0.5, 0.5), &spritesheetFIN, &shaderProgram);
	spriteFIN->setNumberAnimations(4);


	spriteFIN->setAnimationSpeed(0, 8);
	spriteFIN->addKeyframe(0, glm::vec2(0.f, 0.f));

	spriteFIN->setAnimationSpeed(1, 8);
	spriteFIN->addKeyframe(1, glm::vec2(0.5f, 0.f));

	spriteFIN->setAnimationSpeed(2, 8);
	spriteFIN->addKeyframe(2, glm::vec2(0.f, 0.5f));

	spriteFIN->setAnimationSpeed(3, 8);
	spriteFIN->addKeyframe(3, glm::vec2(0.5f, 0.5f));

	spriteFIN->changeAnimation(0);

	tileMapDispl = tileMapPos;
	spriteFIN->setPosition(glm::vec2(float(tileMapDispl.x), float(tileMapDispl.y)));
}

void PantallaLevel2Stage1::update(int deltaTime)
{
	if (mostrar) {
		if (NextLevel) {
			spriteFIN->update(deltaTime);
			if (spriteFIN->animation() == 0 && delayNextLevel < 0) {
				spriteFIN->changeAnimation(1);
				delayNextLevel = 50;
			}
			else if (spriteFIN->animation() == 1 && delayNextLevel < 0) {
				spriteFIN->changeAnimation(2);
				delayNextLevel = 50;
			}
			else if (spriteFIN->animation() == 2 && delayNextLevel < 0) {
				spriteFIN->changeAnimation(3);
				delayNextLevel = 50;
			}
			else if (spriteFIN->animation() == 3 && delayNextLevel < 0) {
				mostrar = false;
			}
			else
				delayNextLevel -= 1;
		}
		else
			sprite->update(deltaTime);
	}
}

void PantallaLevel2Stage1::render()
{
	if (mostrar) {
		if (NextLevel)
			spriteFIN->render();
		else
			sprite->render();
	}
}

void PantallaLevel2Stage1::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

int PantallaLevel2Stage1::getAnimation()
{
	return 0;
}

void PantallaLevel2Stage1::SiguienteNivel()
{
	NextLevel = true;
}

bool PantallaLevel2Stage1::getmostrar()
{
	return mostrar;
}