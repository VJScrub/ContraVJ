#ifndef _BOSS_INCLUDE
#define _BOSS_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
class Boss
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);

	void update(int deltaTime);

	void render();

	void setTileMap(TileMap* tileMap);

	void setPosition(const glm::vec2& pos);

	int getPositionX();

	int getPositionY();

	bool hurted(float x, float y);

	void muerteEnemyPersona();

	bool final();

	int getVidas();

	void setVidas(int _vida);

	void setMostrar(int _mostrar);

	bool getMostrar();

private:
	glm::ivec2 tileMapDispl, posEnemy;
	int  startY;
	Texture spritesheet;
	Texture spritesheetMuerto;
	Sprite* sprite;
	Sprite* spriteMuerto;
	TileMap* map;
	bool muerto;
	int DelayMuerte, altura;
	bool fin;
	int vidas, direccion;
	bool mostrar;
	
};
#endif