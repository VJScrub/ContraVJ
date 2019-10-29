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

enum Dir
{
	RIGHT, RIGHT_UP, UP, RIGHT_DOWN, DOWN, LEFT_DOWN, LEFT, LEFT_UP
};


void Enemy::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, int type)
{
	bJumping = false;
	muerto = false;
	if (type == 1) {
		enemy_type = 1;
		spritesheet.loadFromFile("images/runenemies.png", TEXTURE_PIXEL_FORMAT_RGBA);
		// crear Sprite(quadSize, sizeInSpritesheet, spritesheet, program);
		sprite = Sprite::createSprite(glm::ivec2(16, 32), glm::vec2(0.25, 0.5), &spritesheet, &shaderProgram);
		sprite->setNumberAnimations(5);

		sprite->setAnimationSpeed(STAND_LEFT, 8);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.5f, 0.f));

		sprite->setAnimationSpeed(MOVE_LEFT, 8);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.25f, 0.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.5f, 0.f));

		sprite->setAnimationSpeed(STAND_RIGHT, 8);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.5f, 0.5f));

		sprite->setAnimationSpeed(MOVE_RIGHT, 8);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.5f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25f, 0.5f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5f, 0.5f));

		sprite->changeAnimation(0);
		tileMapDispl = tileMapPos;
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
	}
	else if (type == 2) {
		enemy_type = 2;
		spritesheet.loadFromFile("images/shootenemies2.png", TEXTURE_PIXEL_FORMAT_RGBA);
		// crear Sprite(quadSize, sizeInSpritesheet, spritesheet, program);
		sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 1), &spritesheet, &shaderProgram);
		sprite->setNumberAnimations(4);

		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(0.f, 0.f));

		sprite->setAnimationSpeed(1, 8);
		sprite->addKeyframe(0, glm::vec2(0.25f, 0.f));

		sprite->setAnimationSpeed(2, 8);
		sprite->addKeyframe(1, glm::vec2(0.5f, 0.f));

		sprite->setAnimationSpeed(3, 8);
		sprite->addKeyframe(1, glm::vec2(0.75f, 0.f));

		sprite->changeAnimation(0);
		tileMapDispl = tileMapPos;
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
		delay_shot = 0;
	}
	

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
}

void Enemy::update(int deltaTime, bool act)
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
	else
	{
		if (enemy_type == 1) {
			if (sprite->animation() == MOVE_LEFT) {
				posEnemy.x -= 2;
				if (map->collisionMoveLeft2(posEnemy, glm::ivec2(16, 32)) || (act && !bJumping))
				{
					posEnemy.x += 2;
					if (!bJumping)
					{
						bJumping = true;
						jumpAngle = 0;
						startY = posEnemy.y;
					}
				}
				posEnemy.y += FALL_STEP;
				if (!map->collisionMoveDown2(posEnemy, glm::ivec2(16, 32), &posEnemy.y) && !bJumping)
				{
					posEnemy.x += 4;
					sprite->changeAnimation(MOVE_RIGHT);
				}
				posEnemy.y -= FALL_STEP;
			}
			if (sprite->animation() == MOVE_RIGHT)
			{
				posEnemy.x += 2;
				if (map->collisionMoveRight2(posEnemy, glm::ivec2(16, 32)))
				{
					posEnemy.x -= 2;
					sprite->changeAnimation(MOVE_LEFT);
				}
				posEnemy.y += FALL_STEP;
				if (!map->collisionMoveDown2(posEnemy, glm::ivec2(16, 32), &posEnemy.y)) {
					posEnemy.x -= 2;
					sprite->changeAnimation(MOVE_LEFT);
				}
				posEnemy.y -= FALL_STEP;

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
						bJumping = !map->collisionMoveDown2(posEnemy, glm::ivec2(16, 32), &posEnemy.y);

				}
			}
			else
			{
				posEnemy.y += FALL_STEP;
				if (map->collisionMoveDown2(posEnemy, glm::ivec2(16, 32), &posEnemy.y))
				{
					if (sprite->animation() == STAND_LEFT)
						sprite->changeAnimation(MOVE_LEFT);
				}
			}
		}
		else if (enemy_type == 2) {
			if (posEnemy.y > 6 && posEnemy.y < 12) {
				

			}

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

int Enemy::getDireccion()
{
	if (posEnemy.y >= 6 && posEnemy.y <= 12) {
		return LEFT;
	}
	else if (posEnemy.y < 6) {
		return LEFT_DOWN;
	}
	else if (posEnemy.y < 12) {
		return LEFT_UP;
	}
}

void Enemy::muerteEnemyPersona()
{
	muerto = true;
}

int Enemy::getType() {
	return enemy_type;
}

bool Enemy::final()
{
	return fin;
}

bool Enemy::collision(int x, int y, const glm::ivec2& size) {
	int player_x0 = x / 16;
	int player_x1 = (x + size.x - 1) / 16;
	int player_y0 = y / 16;
	int player_y1 = (y + size.y - 1) / 16;

	int xsize;
	if (enemy_type == 1) {
		xsize = 16;
	}
	else {
		xsize = 32;
	}
	int enemy_x0 = posEnemy.x / 16;
	int enemy_x1 = (posEnemy.x + xsize - 1) / 16;
	int enemy_y0 = posEnemy.y / 16;
	int enemy_y1 = (posEnemy.y + 31) / 16;
	if (((player_x0 < enemy_x1) && (enemy_x0 < player_x1) && (player_y0 < enemy_y1) && (enemy_y0 < player_y1)))
		return true;
	else {
		return false;
	}

}

bool Enemy::getMuerto() {
	return muerto;
}

bool Enemy::time_shot() {
	delay_shot++;
	if (delay_shot == 4) {
		delay_shot = 0;
		return true;
	}
	return false;
}