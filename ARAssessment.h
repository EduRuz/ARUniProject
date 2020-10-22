#ifndef _RENDER_TARGET_APP_H
#define _RENDER_TARGET_APP_H

#include <system/application.h>
#include "State.h"
#include "MenuState.h"
#include "LevelSelectState.h"
#include "GameState.h"
#include "GameOverState.h"

// Images Divisible by 8!!!!!! for VITA
// FRAMEWORK FORWARD DECLARATIONS
namespace gef
{
	class Platform;
	class SpriteRenderer;
	class Font;
	class Renderer3D;
	class Mesh;
	class RenderTarget;
	class TextureVita;
	class InputManager;
}

class ARAssessment : public gef::Application
{
public:

	ARAssessment(gef::Platform& platform, bool vita);
	void Init();
	void CleanUp();
	bool Update(float frameTime);
	void Render();

private:
	void renderOverlay();

	gef::InputManager* inputManager;
	gef::SpriteRenderer* spriteRenderer;
	PrimitiveBuilder* primitiveBuilder;
	class gef::Renderer3D* renderer3d;
	gef::AudioManager* audioManager;

	gef::Font* font;
	float fps;

	bool isSystemVita;//Unused

	//Game State
	gameStates state;
	State* currState;
	MenuState menuState;
	LevelSelectState levelSelectState;
	GameState gameState;
	GameOverState gameOverState;
	
};
#endif // _RENDER_TARGET_APP_H
