#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Enemy.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum EnemyAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, DOWN_RIGHT, DOWN_LEFT
};

void Enemy::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;
	muerto = false;
	spritesheet.loadFromFile("images/runenemies.png", TEXTURE_PIXEL_FORMAT_RGBA);
    // crear Sprite(quadSize, sizeInSpritesheet, spritesheet, program);
	sprite = Sprite::createSprite(glm::ivec2(16, 32), glm::vec2(0.25, 1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(5);

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.25f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.5f, 0.f));



	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));


	spritesheetMuerto.loadFromFile("images/muerteEnemigo.png", TEXTURE_PIXEL_FORMAT_RGBA);
	// crear Sprite(quadSize, sizeInSpritesheet, spritesheet, program);
	spriteMuerto = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 1), &spritesheetMuerto, &shaderProgram);
	spriteMuerto->setNumberAnimations(3);

	spriteMuerto->setAnimationSpeed(0, 8);
	spriteMuerto->addKeyframe(0, glm::vec2(0.f, 0.f));

	spriteMuerto->setAnimationSpeed(1, 8);
	spriteMuerto->addKeyframe(1, glm::vec2(0.25f, 0.f));

	spriteMuerto->setAnimationSpeed(2, 8);
	spriteMuerto->addKeyframe(2, glm::vec2(0.25, 0.5f));

	spriteMuerto->changeAnimation(0);
	spriteMuerto->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));

}

void Enemy::update(int deltaTime)
{

	sprite->update(deltaTime);
	if (muerto == true)
	{
		if (sprite->animation() == 0)
			sprite->changeAnimation(1);
		if (sprite->animation() == 1)
			sprite->changeAnimation(2);
		spriteMuerto->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));

	}
	else
	{
		if (sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		posEnemy.x -= 2;
		if (map->collisionMoveLeft(posEnemy, glm::ivec2(32, 32)))
		{
			posEnemy.x += 2;
			if (!bJumping)
			{
				sprite->changeAnimation(STAND_LEFT);
				bJumping = true;
				jumpAngle = 0;
				startY = posEnemy.y;
			}
		}

		if (bJumping)
		{
			jumpAngle += JUMP_ANGLE_STEP;
			if (jumpAngle == 180)
			{
				bJumping = false;
				posEnemy.y = startY;
			}
			else
			{
				posEnemy.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
				if (jumpAngle > 90)
					bJumping = !map->collisionMoveDown(posEnemy, glm::ivec2(32, 32), &posEnemy.y);
			}
		}
		else
		{
			posEnemy.y += FALL_STEP;
			map->collisionMoveDown(posEnemy, glm::ivec2(32, 32), &posEnemy.y);
		}
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));

	}
}
void Enemy::render()
{
	if (muerto == true)
		spriteMuerto->render();
	else
		sprite->render();
}

void Enemy::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Enemy::setPosition(const glm::vec2& pos)
{
	posEnemy = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
	//spriteMuerto->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

int Enemy::getPositionX() 
{
	return posEnemy.x;
}

int Enemy::getPositionY()
{
	return posEnemy.y;
}

bool Enemy::hurted(float x, float y)
{
	if ((x < (posEnemy.x + 16 ) && x > posEnemy.x) && (y > posEnemy.y && y < posEnemy.y + 32 ))
	{
		return true;
	}
	else
		return false;
}

void Enemy::muerteEnemyPersona()
{
	muerto = true;
}