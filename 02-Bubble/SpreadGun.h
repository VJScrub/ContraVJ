#ifndef _SPREADGUN_INCLUDE
#define _SPREADGUN_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


class SpreadGun
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	bool hurted(float x, float y);
	void setPosition(const glm::vec2& pos);

	void setfinal();

private:
	glm::ivec2 tileMapDispl, posIni;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	bool final;
};

#endif