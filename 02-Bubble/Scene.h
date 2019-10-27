#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "PlayerVertical.h"
#include "Shot.h"
#include <vector>
#include "Enemy.h"
#include "PantallaInicialJP.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void makeShot(bool playershot);
	void render();

	void iniNumberShots(int zero);
private:
	void initShaders();
	void newShot();

	void initEnemies(const string& enemiesFile);

	void newEnemy();


private:
	TileMap* mapPantallaInicial;
	PantallaInicialJP *pijp;
	
	TileMap* mapCreditos;
	
	TileMap *map;
	Player *player;
	vector<Enemy*> enemies;

	TileMap* mapLevel2;
	PlayerVertical *playerVert;

	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	float cameraX, cameraY;
	vector<Shot*> shots;
	bool shotDelay;
	bool creditosDelay;
	int Estado;
};


#endif // _SCENE_INCLUDE

