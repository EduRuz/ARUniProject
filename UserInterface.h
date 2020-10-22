#pragma once
#include <system/platform.h>
#include <graphics\sprite.h>
#include <graphics/sprite_renderer.h>
#include "Player.h"
#include "Enemy.h"
#include "TeamCharacter.h"
#include <vector>

class UserInterface
{
public:
	UserInterface();
	~UserInterface();

	void initUI(gef::Platform& plat, gef::SpriteRenderer* sr, gef::InputManager* input, Player* player, Enemy* enemy);
	void updateUI(std::vector<TeamCharacter*> teamChars, float fps);
	void renderUI(std::vector<TeamCharacter*> teamChars, gef::Platform& platform);

	void playerBattleUI();

private:

	gef::SpriteRenderer* spriteRenderer;
	gef::InputManager* inputManager;

	Player* player;
	Enemy* enemy;
	//UI Elements
	gef::Sprite playerHealthBarBack;
	gef::Sprite playerHealthBar;
	gef::Sprite enemyHealthBarBack;
	gef::Sprite enemyHealthBar;
	gef::Sprite teamOneHealthBarBack;
	gef::Sprite teamOneHealthBar;
	gef::Sprite teamTwoHealthBarBack;
	gef::Sprite teamTwoHealthBar;

	float teamBarWidth;

	gef::Font* font;

	bool playerTurn = false;
	gef::Sprite menuBackground;
	const char * attackText;
	const char * changeCards;

	const char * blank = "";

	bool playerTurnSelection = true;

public:

	bool getPlayerTurn() { return playerTurn; }
	void setPlayerTurn(bool flag) { playerTurn = flag; }

	bool getPlayerTurnSelection() { return playerTurnSelection; }
	void setPlayerTurnSelection(bool flag) { playerTurnSelection = flag; }
};

