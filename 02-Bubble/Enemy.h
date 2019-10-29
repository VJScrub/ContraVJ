#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE

#include "Sprite.h"
#include "TileMap.h"

class Enemy
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, int type);

	void update(int deltaTime, bool act);

	void render();

	void setTileMap(TileMap* tileMap);

	void setPosition(const glm::vec2& pos);

	int getPositionX();

	int getPositionY();

	bool hurted(float x, float y);

	int getDireccion();

	void muerteEnemyPersona();

	int getType();

	bool final();

	bool getMuerto();

	bool collision(int x, int y, const glm::ivec2& size);

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
	int DelayMuerte;

	int enemy_type;
	bool fin;
};

#endif // _ENEMY_INCLUDE