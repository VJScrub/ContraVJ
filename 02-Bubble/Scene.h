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
#include "PantallaLevel2Stage1.h"
#include "PantallaLeve2Boss.h"
#include "EnemyStage2Key.h"
#include "Boss.h"
#include <stdio.h>
#include <irrKlang.h>
#pragma comment(lib, "irrKlang.lib")


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void makeShot(bool playershot, bool vertical);
	void render();

	void iniNumberShots(int zero);
private:
	void initShaders();
	void newShot();

	void initEnemies(const string& enemiesFile);

	void newEnemy();

	void newEnemyKey();

	void changeSound(int _estado);


private:
	TileMap* mapPantallaInicial;
	PantallaInicialJP *pijp;
	
	TileMap* mapCreditos;
	
	TileMap *map;
	Player *player;
	vector<Enemy*> enemies;
	Enemy *currentEnemy;
	int current_x, current_y;

	TileMap* mapLevel2;
	PlayerVertical *playerVert;
	PantallaLevel2Stage1 *Stage1;
	PantallaLeve2Boss *StageBoss;
	bool siguienteNivel;
	vector<EnemyStage2Key*> enemiesKey;
	Boss *finalboss;

	irrklang::ISoundEngine* engine;

	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	float cameraX, cameraY;
	vector<Shot*> shots;
	bool shotDelay;
	bool creditosDelay;
	int Estado;
	int shotBossDelay;
};


#endif // _SCENE_INCLUDE

