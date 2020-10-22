#include "gameState.h"
#include <graphics\sprite.h>
#include <graphics/sprite_renderer.h>
#include <graphics/primitive.h>
#include <sony_sample_framework.h>
#include <sony_tracking.h>
#include <camera.h>
#include <graphics\scene.h>
#include <input/sony_controller_input_manager.h>
#include <graphics/font.h>
#include "load_texture.h"

GameState::GameState(gef::Platform& platform) :
	State(platform)
{
}

/**
	initialise function for the game state level 1.
	@param gef::AudioManager* for audio control in the level.
	@param gef::InputManager* for input control with support for Dualshock 4, Keyboard and PS VITA controls.
	@param gef::spriteRenerer* for rendering 2D sprites to screen.
	@param gef::Renderer3D* for rendering 3D objects.
	@param bool for if running on VITA so no AR code will be run on WINDOWS.
*/
void GameState::init(gef::AudioManager* audioManager_, gef::InputManager* inputManager_, gef::SpriteRenderer* spriteRenderer_, class gef::Renderer3D* renderer3d_, bool vita)
{
	initManagers(audioManager_, inputManager_, spriteRenderer_, renderer3d_, vita);
	currentState = gameStates::GAME;
	isVita = vita;
	primitiveBuilder = new PrimitiveBuilder(platform_);
	initLights();

	crossButtonIcon = CreateTextureFromPNG("playstation-cross-dark-icon.png", platform_);
	triangleButtonIcon = CreateTextureFromPNG("playstation-triangle-dark-icon.png", platform_);
	circleButtonIcon = CreateTextureFromPNG("playstation-circle-dark-icon.png", platform_);
	squareButtonIcon = CreateTextureFromPNG("playstation-square-dark-icon.png", platform_);

	backgroundIcon = CreateTextureFromPNG("StartScreenBackground.png", platform_);

	// initialise sony framework
	sampleInitialize();
	smartInitialize();

	// reset marker tracking
	AppData* dat = sampleUpdateBegin();
	smartTrackingReset();
	sampleUpdateEnd(dat);

	//Camera Feed Code
	cameraFeedTexture = (gef::TextureVita*)gef::Texture::CreateCheckerTexture(640, 10, platform_);
	orthoProject = platform_.OrthographicFrustum(-1, 1, -1, 1, -1, 1);
	vertScale = (960.0f / 544.0f) * (480.0f / 640.0f);

	cameraSprite.set_width(2.0f);
	cameraSprite.set_height(2.0f * vertScale);
	cameraSprite.set_position(0.0f, 0.0f, 1.0f);
	cameraSprite.set_texture(cameraFeedTexture);

	//3D Scene Code
	scaleMatrix.Scale(gef::Vector4(1.0f, vertScale, 1.0f, 1.0f));
	FOVprojectMatrix = platform_.PerspectiveProjectionFov(SCE_SMART_IMAGE_FOV, ((float)SCE_SMART_IMAGE_WIDTH / (float)SCE_SMART_IMAGE_HEIGHT), 0.1f, 50.0f);
	finalProjectMatrix = FOVprojectMatrix * scaleMatrix;
	identityMatrix.SetIdentity();
	
	//Font
	font = new gef::Font(platform_);
	font->Load("comic_sans");
	cardMessage = "";
	currRpgState = rpgState::PLACECARDS;

	//GameObjects
	cube = new GameObject();
	cube->set_mesh(primitiveBuilder->GetDefaultCubeMesh());
	cube->init();
	cube->setPosition(0.0f, 0.f, 0.f);
	cube->setScale(0.059f, 0.059f, 0.059f);
	cube->buildTransform();
	marker1Found = false;

	playerLocked = false;
	player = new Player();
	player->initPlayer(primitiveBuilder, platform_);
	enemy = new Enemy();
	enemy->initFirstBoss(primitiveBuilder, platform_);
	priest = new TeamCharacter();
	priest->initPriest(player, primitiveBuilder, platform_);
	warrior = new TeamCharacter();
	warrior->initWarrior(player, primitiveBuilder, platform_);
	shaman = new TeamCharacter();
	shaman->initShaman(player, primitiveBuilder, platform_);
	ranger = new TeamCharacter();
	ranger->initRanger(player, primitiveBuilder, platform_);
	paladin = new TeamCharacter();
	paladin->initPaladin(player, primitiveBuilder, platform_);

	classCards.clear();
	classCards.push_back(priest);
	classCards.push_back(warrior);
	classCards.push_back(ranger);
	classCards.push_back(paladin);
	classCards.push_back(shaman);

	gameOver = false;

	ui.initUI(platform_,spriteRenderer, inputManager, player, enemy);
}

/**
	Gamestate clean up function.
*/
void GameState::cleanUp()
{
	sharedCleanUp();

	smartRelease();
	sampleRelease();

	priest->cleanUp();
	warrior->cleanUp();
	shaman->cleanUp();
	ranger->cleanUp();
	paladin->cleanUp();
	shaman->cleanUp();

	delete player;
	player = NULL;

	delete enemy;
	enemy = NULL;

	delete priest;
	priest = NULL;

	delete warrior;
	warrior = NULL;

	delete ranger;
	ranger = NULL;

	delete paladin;
	paladin = NULL;

	delete shaman;
	shaman = NULL;

	delete primitiveBuilder;
	primitiveBuilder = NULL;

}

/**
	GameState Update function.
	@param float for fps.
*/
void GameState::update(float fps)
{

	AppData* dat = sampleUpdateBegin();
	gef::Matrix44 marker1Transform;

	//player->updatePlayer(cardsInPlay, fps);
	player->update(fps);
	player->movement(inputManager);
	enemy->update(fps);

	// use the tracking library to try and find markers
	smartUpdate(dat->currentImage);
	gef::Matrix44 tempTransform;
	gef::Matrix44 tempTransform2;

	gef::SonyControllerInputManager* controllerManager = inputManager->controller_input();


	if (sampleIsMarkerFound(player->getMarkerCode())) {

		player->setMarkerFound(true);
		sampleGetTransform(player->getMarkerCode(), &tempTransform);
		player->setMarkerTransform(tempTransform);
		player->set_transform((player->getLocalTransform() * player->getMarkerTransform()));
		
		tempTransform2 = tempTransform;

		tempTransform2.SetTranslation(gef::Vector4((tempTransform.GetTranslation().x() + 0.3000), tempTransform.GetTranslation().y(), tempTransform.GetTranslation().z()));

		enemy->set_transform((enemy->getLocalTransform() * tempTransform2));

		if (controllerManager) {
			const gef::SonyController* controller = controllerManager->GetController(0);
			if (controller->buttons_pressed() & gef_SONY_CTRL_TRIANGLE) {
				playerLocked = true;
			}
		}
	}
	else {
		player->setMarkerFound(false);
	}

	switch (currRpgState)
	{
	case PLACECARDS:
		placeCards();
		break;
	case PLAYERTURN:
		playerTurn();
		break;
	case ENEMYTURN:
		enemyTurn();
		break;
	}

	cardPositionCheck();
	ui.updateUI(cardsInPlay, fps);
	
	if (gameOver == true) {
		requestStateChange(GAMEOVER);
	}

	sampleUpdateEnd(dat);
}

/**
	GameState render funtion.
	@param float for fps.
	@param gef::Font* for a set font for the game. 
	TODO Expand the render function to accept or use multple fonts.
*/
void GameState::render(float fps, gef::Font * font_)
{
	AppData* dat = sampleRenderBegin();

	// REMEMBER AND SET THE PROJECTION MATRIX HERE
	spriteRenderer->set_projection_matrix(orthoProject);

	spriteRenderer->Begin(true);

	if (dat->currentImage) {
		cameraFeedTexture->set_texture(dat->currentImage->tex_yuv);
		spriteRenderer->DrawSprite(cameraSprite);
	}
	
	spriteRenderer->End();

	// SET VIEW AND PROJECTION MATRIX HERE
	renderer3d->set_view_matrix(identityMatrix);
	renderer3d->set_projection_matrix(finalProjectMatrix);
	// Begin rendering 3D meshes, don't clear the frame buffer
	renderer3d->Begin(false);

	if (player->getMarkerFound()) {
		renderer3d->DrawMesh(*player);
		renderer3d->DrawMesh(*enemy);
	}

	if (currRpgState == PLACECARDS){
		for (int i = 0; i < classCards.size(); i++) {
			if (classCards[i]->getMarkerFound()) {
				renderer3d->DrawMesh(*classCards[i]);
			}
		}
	}
	else {
		for (int i = 0; i < cardsInPlay.size(); i++) {
			if (cardsInPlay[i]->getMarkerFound()) {
				renderer3d->DrawMesh(*cardsInPlay[i]);
				//cardsInPlay[i]->getTr
			}
		}
	}

	renderer3d->End();

	ui.renderUI(cardsInPlay, platform_);

	proj_matrix2d = platform_.OrthographicFrustum(0.0f, platform_.width(), 0.0f, platform_.height(), -1.0f, 1.0f);
	spriteRenderer->set_projection_matrix(proj_matrix2d);
	spriteRenderer->Begin(false);

	//Render 2D Components Here


	if (font)
	{
		font->RenderText(spriteRenderer, gef::Vector4(400.f, 500.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_LEFT, cardMessage);
	}

	spriteRenderer->End();

	sampleRenderEnd();
}

/**
	This function can be considered a pseudo-update function for the in game state for finding the two support cards.
	the function is set up to accept the two most recent markers above one registered by the camera.
*/
void GameState::placeCards()
{
	gef::Matrix44 tempTransform;
	cardMessage = "Press X to choose 2 Active Cards";

	cardsInPlay.clear();

	for (int i = 0; i < classCards.size(); i++) {
		if (sampleIsMarkerFound(classCards[i]->getMarkerCode())) {

			classCards[i]->setMarkerFound(true);
			sampleGetTransform(classCards[i]->getMarkerCode(), &tempTransform);
			classCards[i]->setMarkerTransform(tempTransform);
			classCards[i]->set_transform((classCards[i]->getLocalTransform() * classCards[i]->getMarkerTransform()));

			if (cardsInPlay.size() < 2) {
				cardsInPlay.push_back(classCards[i]);
			}
		}
		else {
			classCards[i]->setMarkerFound(false);
		}
	}

	// controller input
	gef::SonyControllerInputManager* controllerManager = inputManager->controller_input();
	if (controllerManager)
	{
		const gef::SonyController* controller = controllerManager->GetController(0);

		if (controller->buttons_pressed() & gef_SONY_CTRL_CROSS) {
			currRpgState = rpgState::PLAYERTURN;
			cardMessage = "";
			ui.setPlayerTurn(true);
		}
	}
}

/**
	This function can be considered a pseudo-update function for the in game state for the players turn.
*/
void GameState::playerTurn()
{
	ui.setPlayerTurn(true);
	gef::Matrix44 tempTransform;

	for (int i = 0; i < cardsInPlay.size(); i++) {
		if (sampleIsMarkerFound(cardsInPlay[i]->getMarkerCode())) {
			
			cardsInPlay[i]->setMarkerFound(true);
			sampleGetTransform(cardsInPlay[i]->getMarkerCode(), &tempTransform);
			cardsInPlay[i]->setMarkerTransform(tempTransform);
			cardsInPlay[i]->set_transform((cardsInPlay[i]->getLocalTransform() * cardsInPlay[i]->getMarkerTransform()));

		}
		else {
		
			cardsInPlay[i]->setMarkerFound(false);
		}
	}

	// controller input
	gef::SonyControllerInputManager* controllerManager = inputManager->controller_input();
	if (controllerManager)
	{
		const gef::SonyController* controller = controllerManager->GetController(0);

		if (controller->buttons_pressed() & gef_SONY_CTRL_CROSS) {
			if (ui.getPlayerTurnSelection()) {
				battleSim();
				//currRpgState = rpgState::ENEMYTURN;
			}
			else {
				currRpgState = rpgState::PLACECARDS;
			}
			ui.setPlayerTurn(false);
		}
	}
}

/**
	This function can be considered a pseudo-update function for the in game state for the enemys turn.
*/
void GameState::enemyTurn()
{

}

/**
	Function for calculating the damage done by all in game characters.
	TODO strip enemy turn damage player turn damage parts to move into respective turn functions.
*/
void GameState::battleSim()
{
	//Enemy
	enemy->dealDamage(player->getCurrAttack());

	if (enemy->getCurrHealth() <= 0) {
		enemy->setAlive(false);
		win = true;
		gameOver = true;
	}

	//Team Char 1
	if (cardsInPlay.size() > 0) {
		if (cardsInPlay[0]->getAlive() == true) {
			enemy->dealDamage(cardsInPlay[0]->getCurrAttack());
			cardsInPlay[0]->dealDamage(enemy->getCurrAttack());
			cardsInPlay[0]->restoreHealth(cardsInPlay[0]->getCurrHealing());
			if (cardsInPlay[0]->getCurrHealth() > cardsInPlay[0]->getMaxHealth()) {
				cardsInPlay[0]->setCurrHealth(cardsInPlay[0]->getMaxHealth());
			}
			if (cardsInPlay[0]->getCurrHealth() <= 0) {
				cardsInPlay[0]->setAlive(false);
				cardsInPlay[0]->setCurrHealth(0);
			}
		}
	}

	//Team Char 2
	if (cardsInPlay.size() > 1) {
		if (cardsInPlay[1]->getAlive() == true) {
			enemy->dealDamage(cardsInPlay[1]->getCurrAttack());
			cardsInPlay[1]->dealDamage(enemy->getCurrAttack());
			cardsInPlay[1]->restoreHealth(cardsInPlay[1]->getCurrHealing());
			if (cardsInPlay[1]->getCurrHealth() > cardsInPlay[1]->getMaxHealth()) {
				cardsInPlay[1]->setCurrHealth(cardsInPlay[1]->getMaxHealth());
			}
			if (cardsInPlay[1]->getCurrHealth() <= 0) {
				cardsInPlay[1]->setAlive(false);
				cardsInPlay[1]->setCurrHealth(0);
			}
		}
	}

	//Player
	player->restoreHealth(player->getCurrHealing());
	player->dealDamage(enemy->getCurrAttack());
	if (player->getCurrHealth() > player->getMaxHealth()) {
		player->setCurrHealth(player->getMaxHealth());
	}
	if (player->getCurrHealth() <= 0) {
		player->setAlive(false);
		win = false;
		gameOver = true;
	}
	

}

/**
	Checks the current position of the support objects in relation to the player to activate buffing abilitys when in the apporpriate position.
	Positions positive of the players position will active the offensive ability.
	Positions negative of the players position will active the defensive ability.
*/
void GameState::cardPositionCheck()
{
	player->resetBuffs();
	gef::Matrix44 playerTransform = player->transform();
	gef::Matrix44 teamTransform;

	if (cardsInPlay.size() > 0) {
		teamTransform = cardsInPlay[0]->transform();
		if (teamTransform.GetTranslation().x() >= playerTransform.GetTranslation().x()){
			cardsInPlay[0]->activateOffensiveAbilty();
		}
		else {
			cardsInPlay[0]->activateDefensiveAbility();
		}
	}

	if (cardsInPlay.size() > 1) {
		teamTransform = cardsInPlay[1]->transform();
		if (teamTransform.GetTranslation().x() >= playerTransform.GetTranslation().x()) {
			cardsInPlay[1]->activateOffensiveAbilty();
		}
		else {
			cardsInPlay[1]->activateDefensiveAbility();
		}
	}
	player->buffPlayer();
}

/**
	initialise the lights for the GameState scene.
*/
void GameState::initLights()
{
	gef::PointLight defaultPointLight;
	defaultPointLight.set_colour(gef::Colour(0.7f, 0.7f, 1.0f, 1.0f));
	defaultPointLight.set_position(gef::Vector4(-300.0f, -500.0f, 100.0f));

	gef::Default3DShaderData& defaultShaderData = renderer3d->default_shader_data();
	defaultShaderData.set_ambient_light_colour(gef::Colour(0.5f, 0.5f, 0.5f, 1.0f));
	defaultShaderData.AddPointLight(default_point_light);
}
