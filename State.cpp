#include "State.h"


//Why cant a platform pointer be set to NULL in the constructer
State::State(gef::Platform& platform) :
	platform_(platform)
{

}

void State::initManagers(gef::AudioManager * audioManager_, gef::InputManager * inputManager_, gef::SpriteRenderer * spriteRenderer_, class gef::Renderer3D* renderer3d_, bool vita)
{
	audioManager = audioManager_;
	inputManager = inputManager_;
	spriteRenderer = spriteRenderer_;
	renderer3d = renderer3d_;

	isVita = vita;
}

void State::sharedCleanUp()
{
	delete crossButtonIcon;
	crossButtonIcon = NULL;

	delete triangleButtonIcon;
	triangleButtonIcon = NULL;

	delete circleButtonIcon;
	circleButtonIcon = NULL;

	delete squareButtonIcon;
	squareButtonIcon = NULL;

	delete backgroundIcon;
	backgroundIcon = NULL;

	spriteRenderer = NULL;

	renderer3d = NULL;

	inputManager = NULL;

	audioManager = NULL;
}

void State::requestStateChange(gameStates stateToChangeTo)
{
	stateChange = true;
	stateToBeLoaded = stateToChangeTo;
}

