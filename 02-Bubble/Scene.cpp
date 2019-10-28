#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include "Shot.h"
#include <GL/glut.h>
#include "PantallaInicialJP.h"
#include "PantallaLevel2Stage1.h"

#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 21

enum CicloVida
{
	Pantalla_Inicial, Level1, Level2, Creditos
};

enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, DOWN_RIGHT, DOWN_LEFT, MOVE_RIGHT_UP, MOVE_LEFT_UP, JUMP
};

enum Dir
{
	RIGHT, RIGHT_UP, UP, RIGHT_DOWN, DOWN, LEFT_DOWN, LEFT, LEFT_UP
};
#define INIT_ENEMY_X_TILES 60
#define INIT_ENEMY_Y_TILES 21



Scene::Scene()
{
	map = NULL;
	player = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
}


void Scene::init()
{
	Estado = Pantalla_Inicial;


	engine = irrklang::createIrrKlangDevice();
	changeSound(Estado);
	

	initShaders();
	//Pantalla Inicial
	mapPantallaInicial = TileMap::createTileMap("levels/PantallaInicial.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	pijp = new PantallaInicialJP();
	pijp->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	pijp->setTileMap(mapPantallaInicial);

	//Creditos
	mapCreditos = TileMap::createTileMap("levels/Creditos.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);


	//Level1  
	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	initEnemies("levels/level01enemies.txt");
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize()/2, INIT_PLAYER_Y_TILES * map->getTileSize()/2));
	player->setTileMap(map);
	
	//Level2
	mapLevel2 = TileMap::createTileMap("levels/level02.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	playerVert = new PlayerVertical();
	playerVert->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	playerVert->setPosition(glm::vec2(INIT_PLAYER_X_TILES * mapLevel2->getTileSize() / 2, INIT_PLAYER_Y_TILES * mapLevel2->getTileSize() / 2));
	playerVert->setTileMap(mapLevel2);
	Stage1 = new PantallaLevel2Stage1();
	Stage1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	StageBoss = new PantallaLeve2Boss();
	StageBoss->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	siguienteNivel = false;
	newEnemyKey();
	enemiesKey[enemiesKey.size() - 1] = new EnemyStage2Key();
	enemiesKey[enemiesKey.size() - 1]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	enemiesKey[enemiesKey.size() - 1]->setPosition(glm::vec2(15 * mapLevel2->getTileSize(), 13.52 * mapLevel2->getTileSize()));
	enemiesKey[enemiesKey.size() - 1]->setTileMap(mapLevel2);
	enemiesKey[enemiesKey.size() - 1]->setVidas(50);
	finalboss = new Boss;
	finalboss->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	finalboss->setPosition(glm::vec2(13.9 * mapLevel2->getTileSize(), 4.2 * mapLevel2->getTileSize()));
	finalboss->setTileMap(mapLevel2);
	finalboss->setVidas(50);

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	cameraX = float(SCREEN_WIDTH - 1);
	cameraY = float(SCREEN_HEIGHT - 1);
	projection = glm::ortho(0.f, cameraX, cameraY, 0.f);
	currentTime = 0.0f;
	creditosDelay = 0;
	shotDelay = true;
	
	shotBossDelay = 100;


}

void Scene::update(int deltaTime)
{
	int x = player->getPositionX();
	int y = player->getPositionY();
	float vx = player->getVX();
	float vy = player->getVY();

	switch (Estado)
	{
	case Pantalla_Inicial:
		
		pijp->update(deltaTime);
		if (Game::instance().getKey('c'))
		{
			if (creditosDelay == false) {
				creditosDelay = true;
				Estado = Creditos;
			}
		}
		else
			creditosDelay = false;
		
		if (Game::instance().getKey('x'))
		{
			Estado = Level2;
			changeSound(Estado);
		}

		break;
	case Level1:

		currentTime += deltaTime;
		player->update(deltaTime);

		for (int k = 0; k < 6; k++) {
			for (int i = 0; i < shots.size(); i++) {

				for (int j = 0; j < enemies.size(); j++) {
					if (enemies[j]->hurted(shots[i]->getPositionX(), shots[i]->getPositionY())) {
						enemies[j]->muerteEnemyPersona();
					}
				}

				if (map->collisionMoveLeft(shots[i]->getPosition(), glm::ivec2(8, 8)))
				{
					shots[i]->fin();
					/*shots.erase(shots.begin() + i);
					i -= 1;*/
				}

				shots[i]->update(deltaTime, false);
			}
		}
		for (int i = 0; i < shots.size(); i++) {
			if (shots[i]->getDist() <= 0) {
				shots.erase(shots.begin() + i);
				i -= 1;
			}

		}

		for (int i = 0; i < enemies.size(); i++) {
			enemies[i]->update(deltaTime);
			if (enemies[i]->final()) {
				enemies.erase(enemies.begin() + i);
				i -= 1;
			}
		}
		
		if (vx > 0) {
			if((cameraX < ((map->returnMapSize().x + 1) * map->getTileSize())) && (player->getPositionX() > ((cameraX-45) - SCREEN_WIDTH/ 2)))
			cameraX += 2;
		}
		else if (vx < 0) {
			if ((cameraX - SCREEN_WIDTH > 0) && (player->getPositionX() < ((cameraX - 45) - SCREEN_WIDTH / 2)))
			cameraX -= 2;
		}

		if (Game::instance().getKey('x'))
		{
			if (shotDelay == false)
			{
				shotDelay = true;
				makeShot(true,false);
			}
			//Shot::init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram)
		}
		else
		{
			shotDelay = false;
		}

		//x += deltaTime * vx;
		//y += deltaTime * vy;
		//x -= cameraX;
		//y -= cameraX;
		//if (x < (SCREEN_X / 3))
		//	cameraX = x + cameraX - SCREEN_X / 3;
		//if (x > (2 * SCREEN_X / 3)) {
		//	cameraX = x + cameraX;
		//	cameraX -= 2 * SCREEN_X / 3;
		//}
		//if (y < (SCREEN_Y / 3))
		//	cameraY = y + cameraY - SCREEN_Y / 3;
		//if (y > (2 * SCREEN_Y / 3)) {
		//	cameraY = y + cameraY;
		//	cameraY -= 2 * SCREEN_Y / 3;
		//}
		projection = glm::ortho(cameraX - SCREEN_WIDTH, cameraX, cameraY, 0.f);


		break;


	case Level2:

	
		currentTime += deltaTime;

		finalboss->update(deltaTime);

		if (finalboss->getMostrar() && shotBossDelay < 0) {
			shotBossDelay = 100;
			newShot();
			shots[shots.size() - 1] = new Shot();
			shots[shots.size() - 1]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 0);
			shots[shots.size() - 1]->BossShot();
			shots[shots.size() - 1]->setPosition(glm::vec2(finalboss->getPositionX(), finalboss->getPositionY()));
			shots[shots.size() - 1]->setTileMap(mapLevel2);
			shots[shots.size() - 1]->VerticalShot();
			
			shots[shots.size() - 1]->Setdist(300);
		}
		else
			shotBossDelay -= 1;
		for (int i = 0; i < enemiesKey.size(); i++) {
			enemiesKey[i]->update(deltaTime);
			if (enemiesKey[i]->final()) {
				enemiesKey.erase(enemiesKey.begin() + i);
				i -= 1;
			}
		}

		for (int k = 0; k < 6; k++) {
			for (int i = 0; i < shots.size(); i++) {
				if (!shots[i]->getBossShot() && finalboss->getMostrar()) {
					if (finalboss->hurted(shots[i]->getPositionX(), shots[i]->getPositionY())) {
						if (finalboss->getVidas() == 0) {
							init();
							Estado = Creditos;
							changeSound(Estado);
						}
						else
							finalboss->setVidas(finalboss->getVidas() - 1);
					}
				}


				for (int j = 0; j < enemiesKey.size(); j++) {
					if (enemiesKey[j]->hurted(shots[i]->getPositionX(), shots[i]->getPositionY())) {
						if (enemiesKey[j]->getVidas() == 0) {
							enemiesKey[j]->muerteEnemyPersona();
							siguienteNivel = true;
							Stage1->SiguienteNivel();
						}
						else
							enemiesKey[j]->setVidas(enemiesKey[j]->getVidas() - 1);
					}
				}

				if (shots[i]->getBossShot()) {
					for (int j = 0; j < shots.size(); j++) {
						if (!shots[j]->getBossShot()) {
							if (shots[i]->hurted(shots[j]->getPositionX(), shots[j]->getPositionY()))
								shots[i]->Setdist(0);
						}
					}
				}

				if (!shots[i]->getBossShot() && mapLevel2->collisionMoveLeft(shots[i]->getPosition(), glm::ivec2(8, 8)))
				{
					shots[i]->fin();
					/*shots.erase(shots.begin() + i);
					i -= 1;*/
				}
				if (shots[i]->getBossShot() && (k / 2 == 0)) {
					shots[i]->update(deltaTime, true);
				}
				else 
					shots[i]->update(deltaTime, true);

			}
		}
		for (int i = 0; i < shots.size(); i++) {
			if (shots[i]->getDist() <= 0  ) {
				shots.erase(shots.begin() + i);
				i -= 1;
			}

		}

		if (Game::instance().getKey('x'))
		{
			if (shotDelay == false)
			{
				shotDelay = true;
				makeShot(true, true);
			}
			//Shot::init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram)
		}
		else
		{
			shotDelay = false;
		}


		Stage1->update(deltaTime);
		StageBoss->update(deltaTime);
		if (siguienteNivel == true && Stage1->getmostrar())
			playerVert->updateRun(deltaTime);
		else
		{
			if (siguienteNivel == true) {
				finalboss->setMostrar(true);
			}
			playerVert->update(deltaTime);
		}
		

		break;

	case Creditos:
		
		if (Game::instance().getKey('x'))
		{
			if (creditosDelay == false) {
				creditosDelay = true;
				Estado = Pantalla_Inicial;
				changeSound(Estado);
			}
			
		}
		else
			creditosDelay = false;
		break;
	}


}

void Scene::makeShot(bool playershot, bool vertical)
{
	newShot();
	shots[shots.size() - 1] = new Shot();
	int direccion;
	float posX, posY;
	if (vertical) {

		direccion = playerVert->getDireccion();

		posX = playerVert->getPositionX();
		posY = playerVert->getPositionY();
	}
	else {
		direccion = player->getDireccion();

		posX = player->getPositionX();
		posY = player->getPositionY();
	}

	if (vertical) {
		switch (direccion)
		{
		case RIGHT:
			posX += 55;
			posY += 5;
			break;

		case LEFT:
			posX += 55;
			break;
		case DOWN_RIGHT:
			direccion = RIGHT;
			posX += 55;
			posY += 20;
			break;
		case DOWN_LEFT:
			direccion = LEFT;
			posX += 55;
			posY += 20;
			break;
		case RIGHT_UP:
			posY += 0;
			break;
		case LEFT_UP:
			posX += 55;
			break;
		case UP:
			posY += 55;
			break;
		default:
			break;
		}
	}
	else {
		switch (direccion)
		{
		case RIGHT:
			posX += 30;
			posY += 5;
			break;

		case LEFT:
			posX -= 10;
			posY += 5;
			break;
		case DOWN_RIGHT:
			direccion = RIGHT;
			posX += 30;
			posY += 15;
			break;
		case RIGHT_UP:
			posX += 20;
			posY += 0;
			break;
		case LEFT_UP:
			posX -= 5;
			posY += 0;
			break;
		case UP:
			posY -= 10;
			break;
		default:
			break;
		}
	}
	shots[shots.size() - 1]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, direccion);
	shots[shots.size() - 1]->setPosition(glm::vec2(posX, posY));
	if (vertical) {
		shots[shots.size() - 1]->setTileMap(mapLevel2);
		shots[shots.size() - 1]->VerticalShot();
	}
	else
		shots[shots.size() - 1]->setTileMap(map);

	if (siguienteNivel)
		shots[shots.size() - 1]->Setdist(300);

	if (playershot)
	{
		shots[shots.size() - 1]->PlayerShot();
	}
}

void Scene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	switch (Estado)
	{
	case Pantalla_Inicial:
		mapPantallaInicial->render();
		pijp->render();
		break;
	case Level1:
		map->render();
		player->render();
		for (int i = 0; i < enemies.size(); i++) {
			enemies[i]->render();
		}
		for (int i = 0; i < shots.size(); i++) {
			shots[i]->render();
		}
		break;

	case Level2:
		mapLevel2->render();
		StageBoss->render();
		Stage1->render();
		finalboss->render();
		playerVert->render();
		for (int i = 0; i < shots.size(); i++) {
			shots[i]->render();
		}
		for (int i = 0; i < enemiesKey.size(); i++) {
			enemiesKey[i]->render();
		}
		break;
	case Creditos:
		mapCreditos->render();
		break;
	}
		
}

void Scene::iniNumberShots(int zero)
{
	shots.clear();
	shots.resize(zero);
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

void Scene::newShot()
{
	shots.resize(shots.size() + 1);
}

void Scene::initEnemies(const string& enemiesFile)
{
	enemies.clear();

	enemies.resize(0);

	ifstream fin;
	string line, tilesheetFile;
	stringstream sstream;
	char tile;
	glm::ivec2 mapSize;

	fin.open(enemiesFile.c_str());
	if (!fin.is_open())
		return;
	getline(fin, line);
	sstream.str(line);
	sstream >> mapSize.x >> mapSize.y;
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetFile;

	for (int j = 0; j < mapSize.y; j++)
	{
		for (int i = 0; i < mapSize.x; i++)
		{
			fin.get(tile);
			if (tile == '$') {
				newEnemy();
				enemies[enemies.size() - 1] = new Enemy();
				enemies[enemies.size() - 1]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				enemies[enemies.size() - 1]->setPosition(glm::vec2(i * map->getTileSize(), j * map->getTileSize()));
				enemies[enemies.size() - 1]->setTileMap(map);
			}
		}
		fin.get(tile);
#ifndef _WIN32
			fin.get(tile);
#endif
		}
		fin.close();
}




void Scene::newEnemy()
{
	enemies.resize(enemies.size() + 1);
}

void Scene::newEnemyKey()
{
	enemiesKey.resize(enemiesKey.size() + 1);
}

void Scene::changeSound(int _estado) {

	switch (Estado)
	{
	case Pantalla_Inicial:
		engine->removeAllSoundSources();
		engine->play2D("sounds/01_-_Contra_-_NES_-_Title.ogg",true);
		break;
	case Level1:
		engine->removeAllSoundSources();
		engine->play2D("sounds/03_-_Contra_-_NES_-_Jungle.ogg", true);
		break;
	case Level2:
		engine->removeAllSoundSources();
		engine->play2D("sounds/04_-_Contra_-_NES_-_Bases.ogg",true);
		break;
	case Creditos:
		engine->removeAllSoundSources();
		engine->play2D("sounds/13_-_Contra_-_NES_-_Victory.ogg", true);
		break;
	default:
		break;
	}
}
