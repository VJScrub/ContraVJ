#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE

#include "Sprite.h"
#include "TileMap.h"

class Enemy
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);

	void update(int deltaTime);

	void render();

	void setTileMap(TileMap* tileMap);

	void setPosition(const glm::vec2& pos);

	int getPositionX();

	int getPositionY();

	bool hurted(float x, float y);

	void muerteEnemyPersona();

private:
	bool bJumping;
	glm::ivec2 tileMapDispl, posEnemy;
	int jumpAngle, startY;
	Texture spritesheet;
	Texture spritesheetMuerto;
	Sprite* sprite;
	Sprite* spriteMuerto;
	TileMap* map;
	bool muerto;
};

#endif // _ENEMY_INCLUDE