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
	void makeShot();
	void render();

	void iniNumberShots(int zero);
private:
	void initShaders();
	void newShot();

	void initEnemies(const string& enemiesFile);

	void newEnemy();


private:
	TileMap *map;
	Player *player;
	vector<Enemy*> enemies;
	Enemy *currentEnemy;
	int current_x, current_y;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	float cameraX, cameraY;
	vector<Shot*> shots;
	bool shotDelay;
};


#endif // _SCENE_INCLUDE

