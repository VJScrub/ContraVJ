#ifndef _ENEMYSTAGE2KEY_INCLUDE
#define _ENEMYSTAGE2KEY_INCLUDE

#include "Sprite.h"
#include "TileMap.h"

class EnemyStage2Key
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
	int vidas;
};
#endif
