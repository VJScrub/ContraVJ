#ifndef _SHOT_INCLUDE
#define _SHOT_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include "Player.h"

#pragma once
class Shot
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int Direc);
	void update(int deltaTime, bool vertical);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

	int getDist();

	int getPositionX();

	int getPositionY();

	glm::ivec2 getPosition();

	void fin();

	void PlayerShot();

	void VerticalShot();

	void Setdist(int distancia);

private:
	glm::ivec2 tileMapDispl, posIni;
	int dist, direccion;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	float offset;
	float  ShotVx, ShotVy;
	bool shotPlayer;
	bool shotVertical;
	int altura;
	
};

#endif