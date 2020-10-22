#pragma once
#include "State.h"
class GameOverState :
	public State
{
public:
	GameOverState(gef::Platform& platform);

	void init(gef::AudioManager* audioManager, gef::InputManager* inputManager, gef::SpriteRenderer* spriteRenderer, class gef::Renderer3D* renderer3d, bool vita);
	void cleanUp() override;
	void update(float fps) override;
	void render(float fps, gef::Font* font_) override;

	bool setWin(bool flag) { win = flag; }

private:
	bool win;
};

