#include "GameOverState.h"
#include "load_texture.h"
#include <graphics/sprite_renderer.h>
#include <graphics/font.h>
#include <input/sony_controller_input_manager.h>
#include <input/keyboard.h>


GameOverState::GameOverState(gef::Platform& platform) :
	State(platform)
{
}

void GameOverState::init(gef::AudioManager* audioManager_, gef::InputManager* inputManager_, gef::SpriteRenderer* spriteRenderer_, class gef::Renderer3D* renderer3d_, bool vita)
{
	initManagers(audioManager_, inputManager_, spriteRenderer_, renderer3d_, vita);
	currentState = gameStates::GAMEOVER;
	isVita = vita;

	crossButtonIcon = CreateTextureFromPNG("playstation-cross-dark-icon.png", platform_);
	triangleButtonIcon = CreateTextureFromPNG("playstation-triangle-dark-icon.png", platform_);
	circleButtonIcon = CreateTextureFromPNG("playstation-circle-dark-icon.png", platform_);
	squareButtonIcon = CreateTextureFromPNG("playstation-square-dark-icon.png", platform_);

	backgroundIcon = CreateTextureFromPNG("GameOverImage.png", platform_);
	background.set_texture(backgroundIcon);
	background.set_position(gef::Vector4(platform_.width()*0.5f, platform_.height()*0.5f, -0.99f));
	background.set_height(544.0f);
	background.set_width(960.0f);
}

void GameOverState::cleanUp()
{
	sharedCleanUp();
}

void GameOverState::update(float fps)
{
	if (isVita == true) {
		const gef::SonyController* controller = inputManager->controller_input()->GetController(0);
		if (controller->buttons_pressed() & gef_SONY_CTRL_CROSS)
		{
			requestStateChange(MENU);

		}
	}
	else {

		const gef::Keyboard* keyboard = inputManager->keyboard();
		if (keyboard)
		{
			if (keyboard->IsKeyPressed(gef::Keyboard::KC_SPACE)) {
				requestStateChange(LEVELSELECT);
			}
		}

	}
}

void GameOverState::render(float fps, gef::Font * font_)
{
	spriteRenderer->Begin();

	spriteRenderer->DrawSprite(background);

	// render "PRESS" text
	font_->RenderText(
		spriteRenderer,
		gef::Vector4(platform_.width()*0.5f, platform_.height()*0.85f - 56.0f, -0.99f),
		1.0f,
		0xffffffff,
		gef::TJ_CENTRE,
		"PRESS");

	// Render button icon
	gef::Sprite button;
	button.set_texture(crossButtonIcon);
	button.set_position(gef::Vector4(platform_.width()*0.5f, platform_.height()*0.85f, -0.99f));
	button.set_height(32.0f);
	button.set_width(32.0f);
	spriteRenderer->DrawSprite(button);



	// render "TO START" text
	font_->RenderText(
		spriteRenderer,
		gef::Vector4(platform_.width()*0.5f, platform_.height()*0.85f + 32.0f, -0.99f),
		1.0f,
		0xffffffff,
		gef::TJ_CENTRE,
		"TO RETURN TO MAIN MENU");



	spriteRenderer->End();
}
