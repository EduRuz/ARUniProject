#pragma once
#include "State.h"
class MenuState :
	public State
{
public:
	MenuState(gef::Platform& platform);

	void init(gef::AudioManager* audioManager, gef::InputManager* inputManager, gef::SpriteRenderer* spriteRenderer, class gef::Renderer3D* renderer3d, bool vita);
	void cleanUp() override;
	void update(float fps) override;
	void render(float fps, gef::Font* font_) override;

private:

};

