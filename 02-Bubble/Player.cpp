#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT,DOWN_RIGHT, DOWN_LEFT, MOVE_RIGHT_UP, MOVE_LEFT_UP, JUMP, STAND_RIGHT_UP, STAND_LEFT_UP
};

enum Dir
{
	RIGHT, RIGHT_UP, UP, RIGHT_DOWN, DOWN, LEFT_DOWN, LEFT, LEFT_UP
};

void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	delayDown = false;
	bJumping = false;
	bdunking = false;
	spritesheet.loadFromFile("images/bub3.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.125, 0.125), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(11);
	
		sprite->setAnimationSpeed(STAND_LEFT, 8);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));
		
		sprite->setAnimationSpeed(STAND_RIGHT, 8);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.125f, 0.f));
		
		sprite->setAnimationSpeed(MOVE_LEFT, 8);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.125f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.25f));
		
		sprite->setAnimationSpeed(MOVE_RIGHT, 8);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.125, 0.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.125, 0.125f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.125, 0.25f));
		
		sprite->setAnimationSpeed(DOWN_RIGHT, 8);
		sprite->addKeyframe(DOWN_RIGHT, glm::vec2(0.f, 0.375f));

		sprite->setAnimationSpeed(DOWN_LEFT, 8);
		sprite->addKeyframe(DOWN_LEFT, glm::vec2(0.125f, 0.375f));

		sprite->setAnimationSpeed(MOVE_RIGHT_UP, 8);
		sprite->addKeyframe(MOVE_RIGHT_UP, glm::vec2(0.25f, 0.f));
		sprite->addKeyframe(MOVE_RIGHT_UP, glm::vec2(0.25f, 0.125f));
		sprite->addKeyframe(MOVE_RIGHT_UP, glm::vec2(0.25f, 0.25f));

		sprite->setAnimationSpeed(MOVE_LEFT_UP, 8);
		sprite->addKeyframe(MOVE_LEFT_UP, glm::vec2(0.375, 0.f));
		sprite->addKeyframe(MOVE_LEFT_UP, glm::vec2(0.375, 0.125f));
		sprite->addKeyframe(MOVE_LEFT_UP, glm::vec2(0.375, 0.25f));

		sprite->setAnimationSpeed(JUMP, 8);
		sprite->addKeyframe(JUMP, glm::vec2(0.5, 0.f));
		sprite->addKeyframe(JUMP, glm::vec2(0.5, 0.125f));
		sprite->addKeyframe(JUMP, glm::vec2(0.5, 0.25f));
		sprite->addKeyframe(JUMP, glm::vec2(0.5, 0.375f));

		sprite->setAnimationSpeed(STAND_RIGHT_UP, 8);
		sprite->addKeyframe(STAND_RIGHT_UP, glm::vec2(0.625f, 0.f));

		sprite->setAnimationSpeed(STAND_LEFT_UP, 8);
		sprite->addKeyframe(STAND_LEFT_UP, glm::vec2(0.625f, 0.125f));



	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	jugadorVx = jugadorVy = 0;
	direccion = RIGHT;
	spreadGun = false;
}

void Player::update(int deltaTime)
{
	AnimacionActual = sprite->animation();
	sprite->update(deltaTime);
	ignoreDownColision = false;
	if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && Game::instance().getSpecialKey(GLUT_KEY_UP))
	{
		if (sprite->animation() != MOVE_RIGHT_UP && !bJumping)
			sprite->changeAnimation(MOVE_RIGHT_UP);
		posPlayer.x += 2;
		jugadorVx = 2;
		direccion = RIGHT_UP;
		if (map->collisionMoveLeft2(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x -= 2;
			jugadorVx = 0;
			sprite->changeAnimation(STAND_RIGHT);
			direccion = RIGHT;
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && Game::instance().getSpecialKey(GLUT_KEY_UP))
	{
		if (sprite->animation() != MOVE_LEFT_UP &&  !bJumping)
			sprite->changeAnimation(MOVE_LEFT_UP);
		posPlayer.x -= 2;
		jugadorVx = -2;
		direccion = LEFT_UP;
		if (map->collisionMoveLeft2(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x += 2;
			jugadorVx = 0;
			sprite->changeAnimation(STAND_LEFT);
			direccion = LEFT;
		}
	}
    else if(Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if(sprite->animation() != MOVE_LEFT &&  !bJumping)
			sprite->changeAnimation(MOVE_LEFT);
		posPlayer.x -= 2;
		jugadorVx = -2;
		direccion = LEFT;
		if(map->collisionMoveLeft2(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x += 2;
			jugadorVx = 0;
			sprite->changeAnimation(STAND_LEFT);
		}
	}
	else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if(sprite->animation() != MOVE_RIGHT &&  !bJumping)
			sprite->changeAnimation(MOVE_RIGHT);
		posPlayer.x += 2;
		jugadorVx = 2;
		direccion = RIGHT;
		if(map->collisionMoveRight2(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x -= 2;
			jugadorVx = 0;
			sprite->changeAnimation(STAND_RIGHT);
		}
	}

	else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN) && Game::instance().getKey(32)) {
			posPlayer.y += FALL_STEP;
	}

	else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN))
	{
		jugadorVx = 0;
		if (sprite->animation() != DOWN_RIGHT &&  !bJumping)
			sprite->changeAnimation(DOWN_RIGHT);
		bdunking = true; 
		if (bJumping)
			direccion = DOWN;
		else
			direccion = DOWN_RIGHT;
		if (map->collisionMoveRight2(posPlayer, glm::ivec2(32, 32)))
		{
			sprite->changeAnimation(STAND_RIGHT);
			direccion = RIGHT;
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_UP))
	{
		if (sprite->animation() == STAND_RIGHT || sprite->animation() == MOVE_RIGHT || sprite->animation() == DOWN_RIGHT)
		{		
			sprite->changeAnimation(STAND_RIGHT_UP);
			direccion = UP;
		}
		else if (sprite->animation() == STAND_LEFT || sprite->animation() == MOVE_LEFT)
		{
			sprite->changeAnimation(STAND_LEFT_UP);
			direccion = UP;
		}
	}
	
	else
	{
		jugadorVx = 0;
		if (sprite->animation() == MOVE_LEFT || sprite->animation() == MOVE_LEFT_UP) {
			sprite->changeAnimation(STAND_LEFT);
			direccion = LEFT;
		}
		else if (sprite->animation() == MOVE_RIGHT || sprite->animation() == MOVE_RIGHT_UP) {
			sprite->changeAnimation(STAND_RIGHT);
			direccion = RIGHT;
		}
		else if (sprite->animation() == DOWN_RIGHT) 
		{
			sprite->changeAnimation(STAND_RIGHT);
			bdunking = FALSE;
		}

	}

	if (Game::instance().getKey(32) && !bJumping)
	{
		if (sprite->animation() == STAND_RIGHT || sprite->animation() == MOVE_RIGHT || sprite->animation() == DOWN_RIGHT || sprite->animation() == MOVE_RIGHT_UP)
		{
			sprite->changeAnimation(JUMP);
			posPlayer.x += 2;
			jugadorVx = 2;
		}
		else if (sprite->animation() == STAND_LEFT || sprite->animation() == MOVE_LEFT || sprite->animation() == MOVE_LEFT_UP)
		{
			sprite->changeAnimation(JUMP);
			posPlayer.x -= 2;
			jugadorVx = -2;
		}

		if (map->collisionMoveRight2(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x -= 2;
			jugadorVx = 0;
		}
		else if (map->collisionMoveLeft2(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x += 2;
			jugadorVx = 0;
		}
	}

	if(bJumping)
	{
		jumpAngle += JUMP_ANGLE_STEP;
		if(jumpAngle == 180)
		{
			bJumping = false;
			posPlayer.y = startY;
			if (direccion == RIGHT || direccion == RIGHT_UP || direccion == RIGHT_DOWN || direccion == UP || direccion == DOWN )
				sprite->changeAnimation(STAND_RIGHT);
			if (direccion == LEFT || direccion == LEFT_UP || direccion == LEFT_DOWN )
				sprite->changeAnimation(STAND_LEFT);
		}
		else
		{
			posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
			if(jumpAngle > 90)
				bJumping = !map->collisionMoveDown2(posPlayer, glm::ivec2(32, 32), &posPlayer.y);
		}
	}
	else
	{
		posPlayer.y += FALL_STEP;

		if(map->collisionMoveDown2(posPlayer, glm::ivec2(32, 32), &posPlayer.y))
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

void Player::render()
{
	sprite->render();
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

int Player::getPositionX()
{
	 return posPlayer.x;
}

int Player::getPositionY()
{
	return posPlayer.y;
}

float Player::getVX()
{
	return jugadorVx;
}

float Player::getVY()
{
	return jugadorVy;
}

int Player::getAnimation()
{
	return AnimacionActual;
}

int Player::getDireccion()
{
	return direccion;
}

void Player::SetSpreadGunTrue() {
	spreadGun = true;
}

bool Player::getSpreadGun(){
	return spreadGun;
}
