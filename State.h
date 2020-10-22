#pragma once
#include <system/application.h>
#include <maths/vector2.h>
#include "primitive_builder.h"
#include <graphics/mesh_instance.h>
#include <audio/audio_manager.h>
#include <input/input_manager.h>
#include <graphics/renderer_3d.h>
#include <graphics/sprite.h>
#include "CameraRu.h"

enum gameStates { MENU, LEVELSELECT, GAME, GAMEOVER};

// FRAMEWORK FORWARD DECLARATIONS
namespace gef
{
	class Platform;
	class SpriteRenderer;
	class Font;
	class Renderer3D;
	class Mesh;
	class Scene;
	class Skeleton;
	class InputManager;
}

class State
{
public:
	State(gef::Platform& platform);

	virtual void init(gef::AudioManager* audioManager, gef::InputManager* inputManager, gef::SpriteRenderer* spriteRenderer, class gef::Renderer3D* renderer3d,  bool vita) {}
	virtual void cleanUp() {}
	virtual void update(float fps) {}
	virtual void render(float fps, gef::Font* font_) {}

	bool getStateChange() { return stateChange; }
	void setStateChange(bool flag) { stateChange = flag; }

	gameStates getcurrentState() { return currentState; }
	void setCurrentState(gameStates flag) { currentState = flag; }

	gameStates getChangeState() { return stateToBeLoaded; }

protected:

	gef::Platform& platform_;

	gef::InputManager* inputManager;
	gef::SpriteRenderer* spriteRenderer;
	gef::AudioManager* audioManager;
	class gef::Renderer3D* renderer3d;

	Camera camera;
	gef::Matrix44 projectionMatrix;
	gef::Matrix44 viewMatrix;

	void initManagers(gef::AudioManager* audioManager, gef::InputManager* inputManager, gef::SpriteRenderer* spriteRenderer, class gef::Renderer3D* renderer3d, bool vita);
	void sharedCleanUp();

	gef::Texture* crossButtonIcon;
	gef::Texture* triangleButtonIcon;
	gef::Texture* circleButtonIcon;
	gef::Texture* squareButtonIcon;
	gef::Texture* backgroundIcon;
	gef::Sprite background;

	void requestStateChange(gameStates stateToChangeTo);
	bool stateChange = false;
	gameStates stateToBeLoaded;

	gameStates currentState;
	
	bool isVita;
};

