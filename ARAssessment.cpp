/**
	The Application is an innovative AR Marker Game that combines AR with turn based combat with real world
	position based interactions.

	@Author Ruaraidh Canaway.
	Games Education Framework supplied by Abertay Univertsity for development on Vita.
*/

#include "arAssessment.h"
#include <system/platform.h>
#include <graphics/font.h>
#include <input/touch_input_manager.h>
#include <maths/vector2.h>
#include <input/input_manager.h>
#include <input/sony_controller_input_manager.h>
#include <input/keyboard.h>
#include <maths/math_utils.h>
#include <graphics/renderer_3d.h>
#include <graphics/render_target.h>


//TOASK memory management with pointers - what about smart pointers?

ARAssessment::ARAssessment(gef::Platform& platform, bool vita) :
	Application(platform),
	inputManager(NULL),
	spriteRenderer(NULL),
	font(NULL),
	renderer3d(NULL),
	primitiveBuilder(NULL),
	audioManager(NULL),
	menuState(platform),
	levelSelectState(platform),
	gameState(platform),
	gameOverState(platform)
{
	isSystemVita = vita;
}

/**
	Initialiser function for the AR assessment StateMachine
*/
void ARAssessment::Init()
{
	inputManager = gef::InputManager::Create(platform_);
	spriteRenderer = gef::SpriteRenderer::Create(platform_);
	renderer3d = gef::Renderer3D::Create(platform_);
	primitiveBuilder = new PrimitiveBuilder(platform_);
	audioManager = gef::AudioManager::Create();

	font = new gef::Font(platform_);
	font->Load("comic_sans");

	currState = &menuState;
	currState->setCurrentState(gameStates::MENU);

	//currState = &gameState;
	//currState->setCurrentState(gameStates::GAME);
	currState->init(audioManager, inputManager, spriteRenderer, renderer3d, isSystemVita);

}

/**
	Clean Up for pointer variables
*/
void ARAssessment::CleanUp()
{
	delete primitiveBuilder;
	primitiveBuilder = NULL;

	delete font;
	font = NULL;

	delete spriteRenderer;
	spriteRenderer = NULL;

	delete renderer3d;
	renderer3d = NULL;

	delete inputManager;
	inputManager = NULL;

	delete audioManager;
	audioManager = NULL;
}

/**
	Update function for State Machine control
	@param float for frame time to calculate current FPS
*/
bool ARAssessment::Update(float frameTime)
{
	fps = 1.0f / frameTime;

	inputManager->Update();

	if (currState->getStateChange() == true) {
		currState->setStateChange(false);
		currState->cleanUp();
		

		switch (currState->getChangeState()) {
		
		case gameStates::MENU:
			currState = &menuState;
			break;

		case gameStates::LEVELSELECT:
			currState = &levelSelectState;
			break;

		case gameStates::GAME:
			currState = &gameState;
			break;

		case gameStates::GAMEOVER:
			currState = &gameOverState;
			gameOverState.setWin(gameState.getWin());
			break;
		
		}
		currState->init(audioManager, inputManager, spriteRenderer, renderer3d, isSystemVita);
	}

	const gef::Keyboard* keyboard = inputManager->keyboard();
	if (keyboard)
	{
		if (keyboard->IsKeyPressed(gef::Keyboard::KC_ESCAPE)) {
			return false;
		}
	}

	currState->update(fps);

	return true;
}

/**
	Render function for current active state
*/
void ARAssessment::Render()
{

	currState->render(fps, font);

	renderOverlay();
}

/**
	Draws the fps text on top of every state.
*/
void ARAssessment::renderOverlay()
{
	gef::Matrix44 proj_matrix2d;

	proj_matrix2d = platform_.OrthographicFrustum(0.0f, platform_.width(), 0.0f, platform_.height(), -1.0f, 1.0f);
	spriteRenderer->set_projection_matrix(proj_matrix2d);
	spriteRenderer->Begin(false);
	
	if (font)
	{
		font->RenderText(spriteRenderer, gef::Vector4(850.0f, 510.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_LEFT, "FPS: %.1f", fps);
	}

	spriteRenderer->End();
}


