#ifndef _Vida_INCLUDE
#define _Vida_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
class vida
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

	bool getMostrar();

	void setMostrar(bool _mostrar);

private:
	glm::ivec2 tileMapDispl, posIni;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;

	bool mostrar;
};

#endif