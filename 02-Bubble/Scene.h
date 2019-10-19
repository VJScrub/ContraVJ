#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Shot.h"
#include <vector>
#include "Enemy.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();

	void iniNumberShots(int zero);
private:
	void initShaders();
	void newShot();

private:
	TileMap *map;
	Player *player;
	Enemy *enemy;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	float cameraX, cameraY;
	vector<Shot*> shots;
};


#endif // _SCENE_INCLUDE

