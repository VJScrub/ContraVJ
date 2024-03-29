#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	void recover();
	
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);

	int getPositionX();

	int getPositionY();

	float getVX();

	float getVY();

	int getAnimation();

	int getDireccion();

	bool die();

	void SetSpreadGunTrue();

	bool getSpreadGun();


	
private:
	bool bJumping;
	bool bdunking;
	glm::ivec2 tileMapDispl, posPlayer;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	int direccion, lives;

	int AnimacionActual;
	float  jugadorVx, jugadorVy;
	bool delayDown;
	bool spreadGun;
};


#endif // _PLAYER_INCLUDE


