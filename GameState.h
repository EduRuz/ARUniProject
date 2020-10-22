#pragma once
#include "State.h"
#ifndef WIN32
#include <platform/vita/graphics/texture_vita.h> //TODO comment out when not on Vita
#endif // WIN32
#include "Player.h"
#include "Enemy.h"
#include "TeamCharacter.h"
#include <graphics/mesh_instance.h>
#include <vector>
// Vita AR includes
#include <camera.h>
#include <gxm.h>
#include <motion.h>
#include <libdbg.h>
#include <libsmart.h>
#include "GameObject.h"
#include "math.h"
#include "UserInterface.h"

class GameState :
	public State
{
public:
	GameState(gef::Platform& platform);

	void init(gef::AudioManager* audioManager, gef::InputManager* inputManager, gef::SpriteRenderer* spriteRenderer, class gef::Renderer3D* renderer3d, bool vita);
	void cleanUp() override;
	void update(float fps) override;
	void render(float fps, gef::Font* font_) override;
	bool getWin() { return win; }
private:

	void placeCards();
	void playerTurn();
	void enemyTurn();
	void battleSim();
	void cardPositionCheck();

	bool win;
	bool gameOver;

	enum rpgState { PLACECARDS, PLAYERTURN, ENEMYTURN, BATLLESIM };

	void initLights();

	PrimitiveBuilder* primitiveBuilder;
	bool marker1Found;

	//Rendering Camera Feed
	gef::Matrix44 orthoProject;
	float vertScale;
	gef::Sprite cameraSprite;
	gef::TextureVita *cameraFeedTexture;

	//Rendering 3D Scene
	gef::Matrix44 scaleMatrix;
	gef::Matrix44 FOVprojectMatrix;
	gef::Matrix44 finalProjectMatrix;
	gef::Matrix44 identityMatrix;
	gef::Matrix44 proj_matrix2d;

	UserInterface ui;

	GameObject* cube;

	Player* player;
	Enemy* enemy;
	TeamCharacter* priest;
	TeamCharacter* warrior;
	TeamCharacter* shaman;
	TeamCharacter* ranger;
	TeamCharacter* paladin;

	std::vector<TeamCharacter*> classCards;
	std::vector<TeamCharacter*> cardsInPlay;
	const char * cardMessage;

	rpgState currRpgState;
	gef::Font* font;

	bool playerLocked;
};

