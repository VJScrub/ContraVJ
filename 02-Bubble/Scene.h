#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
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

private:
	void initShaders();

	void initEnemies(const string& enemiesFile);

	void newEnemy();


private:
	TileMap *map;
	Player *player;
	vector<Enemy*> enemies;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	float cameraX, cameraY;
};


#endif // _SCENE_INCLUDE

