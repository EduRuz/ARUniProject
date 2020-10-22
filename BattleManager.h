#pragma once
#include <system/platform.h>
#include <graphics\sprite.h>
#include <graphics/sprite_renderer.h>
#include "Player.h"
#include "Enemy.h"
#include "TeamCharacter.h"
#include <vector>

class BattleManager
{
public:
	BattleManager();
	~BattleManager();

	void init(gef::SpriteRenderer* sr, Player* p, Enemy* e);
	void update(float fps_);
	void render(gef::Platform& plat);


private:
	enum rpgState { START, PLACECARDS, PLAYERTURN, ENEMYTURN };

	rpgState currRpgState;
	gef::Font* font;

};

