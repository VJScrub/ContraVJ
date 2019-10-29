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
#include "SpreadGun.h"
#include "EnemyStage3.h"
#include "vida.h"
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
	void makeShotEnemy(bool playershot, bool vertical, float posX, float posY, int direccion);

	void render();

	void player_status(int playerx, int playery);

	void player_status2(int playerx, int playery);

	void iniNumberShots(int zero);
private:
	void initShaders();
	void newShot();

	void initEnemies(const string& enemiesFile);

	void newEnemy();

	void newVida();

	void newEnemyKey();

	void newEnemy3();

	void changeSound(int _estado);

	void iniciar();

	void iniciarEnemies3();


private:
	TileMap* mapPantallaInicial;
	PantallaInicialJP *pijp;
	vector<vida*> vidas;

	TileMap* mapCreditos;
	TileMap* mapIns;
	TileMap* mapContinue;

	TileMap *map;
	Player *player;
	vector<Enemy*> enemies;
	Enemy *currentEnemy;

	int current_x, current_y, player_x, player_y;;
	int colision_x, colision_y, player_lives;
	int delay_enemy_shoot;
	bool act;

	SpreadGun *sp;

	TileMap* mapLevel2;
	PlayerVertical *playerVert;
	PantallaLevel2Stage1 *Stage1;
	PantallaLeve2Boss *StageBoss;
	bool siguienteNivel;
	vector<EnemyStage2Key*> enemiesKey;
	vector<EnemyStage3*> enemies3;

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
	bool InsDelay;
	bool PIDelay;
	int delay;
	int delay2;
	bool pymuerto;
};


#endif // _SCENE_INCLUDE

