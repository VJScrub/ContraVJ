#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"



#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 21

#define INIT_ENEMY_X_TILES 60
#define INIT_ENEMY_Y_TILES 21


Scene::Scene()
{
	map = NULL;
	player = NULL;
	enemy = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
	if (enemy != NULL)
		delete enemy;
}


void Scene::init()
{
	initShaders();
	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize()/2, INIT_PLAYER_Y_TILES * map->getTileSize()/2));
	player->setTileMap(map);
	enemy = new Enemy();
	enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	enemy->setPosition(glm::vec2(INIT_ENEMY_X_TILES * map->getTileSize(), INIT_ENEMY_Y_TILES * map->getTileSize()));
	enemy->setTileMap(map);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	cameraX = float(SCREEN_WIDTH - 1);
	cameraY = float(SCREEN_HEIGHT - 1);
	projection = glm::ortho(0.f, cameraX, cameraY, 0.f);
	currentTime = 0.0f;
	
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
	enemy->update(deltaTime);

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



