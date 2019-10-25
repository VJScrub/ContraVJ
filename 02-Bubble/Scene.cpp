#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include "Shot.h"
#include <GL/glut.h>


#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 21

enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, DOWN_RIGHT, DOWN_LEFT
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
	initShaders();
	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	initEnemies("levels/level01enemies.txt");
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize()/2, INIT_PLAYER_Y_TILES * map->getTileSize()/2));
	player->setTileMap(map);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	cameraX = float(SCREEN_WIDTH - 1);
	cameraY = float(SCREEN_HEIGHT - 1);
	projection = glm::ortho(0.f, cameraX, cameraY, 0.f);
	currentTime = 0.0f;
	shotDelay = 0;
	
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
	
	for (int k = 0; k < 6; k++) {
		for (int i = 0; i < shots.size(); i++) {
			if (map->collisionMoveLeft(shots[i]->getPosition(), glm::ivec2(8, 8)))
			{
				shots[i]->fin();
				/*shots.erase(shots.begin() + i);
				i -= 1;*/
			}

			shots[i]->update(deltaTime);
		}
	}
	for (int i = 0; i < shots.size(); i++) {
		if (shots[i]->getDist() <= 0) {
			shots.erase(shots.begin()+i);
			i -= 1;
		}

	}

	for (int k = 0; k < 6; k++) {
		for (int i = 0; i < shots.size(); i++) {
			if (map->collisionMoveLeft(shots[i]->getPosition(), glm::ivec2(8, 8)))
			{
				shots[i]->fin();
				/*shots.erase(shots.begin() + i);
				i -= 1;*/
			}

			shots[i]->update(deltaTime);
		}
	}
	for (int i = 0; i < shots.size(); i++) {
		if (shots[i]->getDist() <= 0) {
			shots.erase(shots.begin()+i);
			i -= 1;
		}

	}
	enemy->update(deltaTime);
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i]->update(deltaTime);
	}

	int x = player->getPositionX();
	int y = player->getPositionY();
	float vx = player->getVX();
	float vy = player->getVY();
	


	if (vx > 0) {
		cameraX += 2;
	}
	else if (vx < 0) {
		cameraX -= 2;
	}
	if (Game::instance().getKey('c')) 
	{
		if (shotDelay == false)
		{
			shotDelay = true;
			makeShot();
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
	projection = glm::ortho(cameraX-SCREEN_WIDTH, cameraX, cameraY, 0.f);

}

void Scene::makeShot()
{
	newShot();
	shots[shots.size() - 1] = new Shot();
	int direccion;
	float posX, posY;
	posX = player->getPositionX();
	posY = player->getPositionY();
	switch (player->getAnimation())
	{
	case STAND_RIGHT:
		direccion = RIGHT;
		posX += 30;
		posY += 5;
		break;
	case MOVE_RIGHT:
		direccion = RIGHT;
		posX += 30;
		posY += 5;
		break;
	case STAND_LEFT:
		direccion = LEFT;
		posX -= 10;
		posY += 5;
		break;
	case MOVE_LEFT:
		direccion = LEFT;
		posX -= 10;
		posY += 5;
		break;
	case DOWN_RIGHT:
		direccion = RIGHT;
		posX += 30;
		posY += 15;
		break;
	default:
		break;
	}
	shots[shots.size() - 1]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, direccion);
	shots[shots.size() - 1]->setPosition(glm::vec2(posX, posY));
	shots[shots.size() - 1]->setTileMap(map);
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
	map->render();
	player->render();
	enemy->render();
	
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




