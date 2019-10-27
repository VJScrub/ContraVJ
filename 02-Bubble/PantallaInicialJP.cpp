#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "PantallaInicialJP.h"
#include "Game.h"


enum PIAnims
{
	Primera
};

void PantallaInicialJP::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/PIJaponesa.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(512, 512), glm::vec2(0.5, 0.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);


	sprite->setAnimationSpeed(Primera, 8);
	sprite->addKeyframe(Primera, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(Primera, glm::vec2(0.5f, 0.f));
	sprite->addKeyframe(Primera, glm::vec2(0.f, 0.5f));
	sprite->addKeyframe(Primera, glm::vec2(0.5f, 0.5f));

	sprite->changeAnimation(0);

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x ), float(tileMapDispl.y)));

}

void PantallaInicialJP::update(int deltaTime)
{
	sprite->update(deltaTime);
}

void PantallaInicialJP::render()
{
	sprite->render();
}

void PantallaInicialJP::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

int PantallaInicialJP::getAnimation()
{
	return 0;
}
