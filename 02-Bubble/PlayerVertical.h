#ifndef _PLAYERVert_INCLUDE
#define _PLAYERVert_INCLUDE
#include "Sprite.h"
#include "TileMap.h"

class PlayerVertical
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void updateRun(int deltaTime);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

	int getPositionX();

	int getPositionY();

	float getVX();

	float getVY();

	int getAnimation();

	int getDireccion();

	float getposIniY();

	bool die();

	void setvidas(int _lives);

	int getvidas();

private:
	bool bJumping;
	glm::ivec2 tileMapDispl, posPlayer;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	int direccion,profundidad, altura, lives;

	int AnimacionActual;
	float  jugadorVx, jugadorVy;

	float posIniY;
};
#endif

