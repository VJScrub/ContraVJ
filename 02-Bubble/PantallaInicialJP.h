#ifndef _PANTALLAINICIALJP_INCLUDE
#define _PANTALLAINICIALJP_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
class PantallaInicialJP
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
};

#endif 