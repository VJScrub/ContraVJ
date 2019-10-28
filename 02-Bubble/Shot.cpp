#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Shot.h"
#include "Player.h"
#include "Game.h"


enum Dir
{
	RIGHT, RIGHT_UP, UP, RIGHT_DOWN, DOWN, LEFT_DOWN, LEFT, LEFT_UP
};

void Shot::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int Direcc)
{
	spritesheet.loadFromFile("images/shot.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(1, 8);
	sprite->addKeyframe(1, glm::vec2(0.25, 0.25f));
	sprite->addKeyframe(1, glm::vec2(0.25, 0.5f));

	
	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posIni.x), float(tileMapDispl.y + posIni.y)));
	ShotVx = ShotVx = 0;

	direccion = Direcc;
	dist = 1000; //Distancia que la bala vive

	shotPlayer = false;
	shotVertical = false;
	altura = 20;
}

void Shot::update(int deltaTime, bool vertical)
{
	sprite->update(deltaTime);
	dist -= 1;
	
	if (vertical) {
		switch (direccion)
		{
		case RIGHT:
			posIni.y -= 0.25f;
			break;
		case LEFT:
			posIni.y -= 0.25f;
			break;
		case RIGHT_UP:
			posIni.y -= 0.25f;
			break;
		case LEFT_UP:
			posIni.y -= 0.25f;
			break;
		case UP:
			posIni.y -= 0.25f;
			break;
		case DOWN:
			posIni.y -= 0.25f;
			altura = 0;
			break;
		default:
			break;
		}
	}
	else {
		switch (direccion)
		{
		case RIGHT:
			posIni.x += 1;
			break;
		case LEFT:
			posIni.x -= 1;
			break;
		case RIGHT_UP:
			posIni.x += 1;
			posIni.y -= 1;
			break;
		case LEFT_UP:
			posIni.x -= 1;
			posIni.y -= 1;
			break;
		case UP:
			posIni.y -= 1;
			break;
		case DOWN:
			posIni.y += 1;
			break;
		default:
			break;
		}
	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posIni.x), float(tileMapDispl.y + posIni.y)));
}

void Shot::render()
{
	sprite->render();
}

void Shot::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Shot::setPosition(const glm::vec2& pos)
{
	posIni = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posIni.x), float(tileMapDispl.y + posIni.y)));

}

int Shot::getDist()
{
	return dist;
}

int Shot::getPositionX()
{
	return posIni.x;
}

int Shot::getPositionY()
{
	return posIni.y;
}

glm::ivec2 Shot::getPosition()
{
	return posIni;
}

void Shot::fin()
{
	sprite->changeAnimation(1);
}

void Shot::PlayerShot()
{
	shotPlayer = true;
}

void Shot::VerticalShot()
{
	shotVertical = true;
	dist = 50;
}

void Shot::Setdist(int distancia)
{
	dist = distancia;
}