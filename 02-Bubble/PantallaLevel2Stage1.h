#ifndef _PANTALLALEVEL2STAGE1_INCLUDE
#define _PANTALLALEVEL2STAGE1_INCLUDE
#include "Sprite.h"
#include "TileMap.h"

class PantallaLevel2Stage1
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	int getAnimation();
	void SiguienteNivel();
	bool getmostrar();
private:
	Texture spritesheet;
	Sprite* sprite;

	Texture spritesheetFIN;
	Sprite* spriteFIN;

	TileMap* map;
	glm::ivec2 tileMapDispl;
	bool NextLevel;
	int delayNextLevel;
	bool mostrar;
};
#endif
