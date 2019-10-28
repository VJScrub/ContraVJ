#include "PlayerVertical.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4

enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, DOWN_RIGHT, DOWN_LEFT, MOVE_RIGHT_UP, MOVE_LEFT_UP, JUMP, RUN
};

enum Dir
{
	RIGHT, RIGHT_UP, UP, RIGHT_DOWN, DOWN, LEFT_DOWN, LEFT, LEFT_UP
};


void PlayerVertical::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	bJumping = false;
	posIniY = -1234;
	profundidad = 50;
	altura = 20; 
	spritesheet.loadFromFile("images/PlayerVertical.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(128, 128), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(10);

		sprite->setAnimationSpeed(STAND_LEFT, 8);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.25f, 0.f));

		sprite->setAnimationSpeed(STAND_RIGHT, 8);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.f));

		sprite->setAnimationSpeed(MOVE_LEFT, 8);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.25f, 0.25f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.25f, 0.5f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.25f, 0.75f));

		sprite->setAnimationSpeed(MOVE_RIGHT, 8);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.25f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.5f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.75f));

		sprite->setAnimationSpeed(DOWN_RIGHT, 8);
		sprite->addKeyframe(DOWN_RIGHT, glm::vec2(0.5f, 0.5f));

		sprite->setAnimationSpeed(DOWN_LEFT, 8);
		sprite->addKeyframe(DOWN_LEFT, glm::vec2(0.5f, 0.25f));

		sprite->setAnimationSpeed(MOVE_RIGHT_UP, 8);
		//sprite->addKeyframe(MOVE_RIGHT_UP, glm::vec2(0.25f, 0.f));
		//sprite->addKeyframe(MOVE_RIGHT_UP, glm::vec2(0.25f, 0.125f));
		//sprite->addKeyframe(MOVE_RIGHT_UP, glm::vec2(0.25f, 0.25f));

		sprite->setAnimationSpeed(MOVE_LEFT_UP, 8);
		//sprite->addKeyframe(MOVE_LEFT_UP, glm::vec2(0.375, 0.f));
		//sprite->addKeyframe(MOVE_LEFT_UP, glm::vec2(0.375, 0.125f));
		//sprite->addKeyframe(MOVE_LEFT_UP, glm::vec2(0.375, 0.25f));

		sprite->setAnimationSpeed(JUMP, 8);
		sprite->addKeyframe(JUMP, glm::vec2(0.75, 0.f));
		sprite->addKeyframe(JUMP, glm::vec2(0.75, 0.25f));
		sprite->addKeyframe(JUMP, glm::vec2(0.75, 0.5f));
		sprite->addKeyframe(JUMP, glm::vec2(0.75, 0.75f));

		sprite->setAnimationSpeed(RUN, 8);
		sprite->addKeyframe(RUN, glm::vec2(0.5f, 0.f));
		sprite->addKeyframe(RUN, glm::vec2(0.5f, 0.75f));

		sprite->changeAnimation(1);
		tileMapDispl = tileMapPos;
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
		jugadorVx = jugadorVy = 0;
		direccion = RIGHT;
}

void PlayerVertical::updateRun(int deltaTime) {
	AnimacionActual = sprite->animation();
	sprite->update(deltaTime);

	if (sprite->animation() != RUN)
		sprite->changeAnimation(RUN);

	if (posIniY == -1234)
		posIniY = posPlayer.y;

	if (posPlayer.y > (posIniY - 50))
		posPlayer.y -= 1;
	else
		posPlayer.y = posIniY;

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void PlayerVertical::update(int deltaTime)
{
	AnimacionActual = sprite->animation();
	sprite->update(deltaTime);

	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if (sprite->animation() != MOVE_LEFT && !bJumping)
			sprite->changeAnimation(MOVE_LEFT);
		posPlayer.x -= 2;
		jugadorVx = -2;
		direccion = LEFT;
		altura = 20;
		if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x += 2;
			jugadorVx = 0;
			sprite->changeAnimation(STAND_LEFT);
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if (sprite->animation() != MOVE_RIGHT && !bJumping)
			sprite->changeAnimation(MOVE_RIGHT);
		posPlayer.x += 2;
		jugadorVx = 2;
		direccion = RIGHT;
		altura = 20;
		if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x -= 2;
			jugadorVx = 0;
			sprite->changeAnimation(STAND_RIGHT);
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN))
	{
		jugadorVx = 0;
		if (direccion == RIGHT || direccion == RIGHT_UP || direccion == RIGHT_DOWN || direccion == DOWN)
		{
			if (sprite->animation() != DOWN_RIGHT && !bJumping)
				sprite->changeAnimation(DOWN_RIGHT);
		}
		if (direccion == LEFT || direccion == LEFT_UP || direccion == LEFT_DOWN)
			if (sprite->animation() != DOWN_LEFT && !bJumping)
				sprite->changeAnimation(DOWN_LEFT);
		direccion = UP;
		altura = 0;
		
		if (bJumping)
			direccion = DOWN;
		else
			direccion = DOWN_RIGHT;
		if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
		{
			sprite->changeAnimation(STAND_RIGHT);
			direccion = RIGHT;
		}
	}
	else
	{
		jugadorVx = 0;
		altura = 20;
		if (sprite->animation() == MOVE_LEFT || sprite->animation() == MOVE_LEFT_UP || sprite->animation() == DOWN_LEFT) {
			sprite->changeAnimation(STAND_LEFT);
			direccion = LEFT;
		}
		else if (sprite->animation() == MOVE_RIGHT || sprite->animation() == MOVE_RIGHT_UP || sprite->animation() == DOWN_RIGHT) {
			sprite->changeAnimation(STAND_RIGHT);
			direccion = RIGHT;
		}
	}
	if (Game::instance().getKey(32) && !bJumping)
	{
		if (sprite->animation() == STAND_RIGHT || sprite->animation() == MOVE_RIGHT || sprite->animation() == DOWN_RIGHT)
		{
			sprite->changeAnimation(JUMP);
			posPlayer.x += 2;
			jugadorVx = 2;
		}
		else if (sprite->animation() == STAND_LEFT || sprite->animation() == MOVE_LEFT || sprite->animation() == DOWN_LEFT)
		{
			sprite->changeAnimation(JUMP);
			posPlayer.x -= 2;
			jugadorVx = -2;
		}

		if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x -= 2;
			jugadorVx = 0;
		}
		else if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x += 2;
			jugadorVx = 0;
		}
	}


	if (bJumping)
	{
		jumpAngle += JUMP_ANGLE_STEP;
		if (jumpAngle == 180)
		{
			bJumping = false;
			posPlayer.y = startY;
			if (direccion == RIGHT || direccion == RIGHT_UP || direccion == RIGHT_DOWN || direccion == UP || direccion == DOWN) {
				altura = 20;
				sprite->changeAnimation(STAND_RIGHT);

			}
			if (direccion == LEFT || direccion == LEFT_UP || direccion == LEFT_DOWN) {
				altura = 20;
				sprite->changeAnimation(STAND_LEFT);
			}
		}
		else
		{
			posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
			/*if (jumpAngle > 90)
				bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y);*/
		}
	}
	else
	{
		posPlayer.y += FALL_STEP;
		if (map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y))
		{
			if (Game::instance().getKey(32))
			{
				bJumping = true;
				jumpAngle = 0;
				startY = posPlayer.y;
			}
		}
	}
	
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}

void PlayerVertical::render()
{
	sprite->render();
}

void PlayerVertical::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void PlayerVertical::setPosition(const glm::vec2& pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}

int PlayerVertical::getPositionX()
{
	return posPlayer.x;
}

int PlayerVertical::getPositionY()
{
	return posPlayer.y;
}

float PlayerVertical::getVX()
{
	return jugadorVx;
}

float PlayerVertical::getVY()
{
	return jugadorVy;
}

int PlayerVertical::getAnimation()
{
	return AnimacionActual;
}

int PlayerVertical::getDireccion()
{
	return direccion;
}

float PlayerVertical::getposIniY()
{
	return posIniY;
}
