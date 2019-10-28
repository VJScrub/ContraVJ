#ifndef _PANTALLALEVEL2BOSS_INCLUDE
#define _PANTALLALEVEL2BOSS_INCLUDE
#include "Sprite.h"
#include "TileMap.h"

class PantallaLeve2Boss
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	int getAnimation();
private:
	Texture spritesheet;
	Sprite* sprite;

	TileMap* map;
	glm::ivec2 tileMapDispl;
	bool NextLevel;
	int delayNextLevel;
	bool mostrar;
};

#endif