#include "UserInterface.h"
#include <graphics/font.h>
#include <input/sony_controller_input_manager.h>
#include <input/input_manager.h>

UserInterface::UserInterface() :
	spriteRenderer(NULL),
	inputManager(NULL)
{
}


UserInterface::~UserInterface()
{
}

void UserInterface::initUI(gef::Platform& plat, gef::SpriteRenderer * sr, gef::InputManager* input,  Player * p, Enemy * e)
{
	spriteRenderer = sr;
	inputManager = input;
	player = p;
	enemy = e;

	//Player Health Bar
	playerHealthBarBack.set_position(gef::Vector4(175.0f, 510.0f, -0.99f));
	playerHealthBarBack.set_height(20.0f);
	playerHealthBarBack.set_width(300.0f);
	playerHealthBarBack.set_colour(0xFF000000);

	playerHealthBar.set_position(gef::Vector4(175.0f, 510.0f, -0.99f));
	playerHealthBar.set_height(20.0f);
	playerHealthBar.set_width(300.0f);
	playerHealthBar.set_colour(0xFF51F542);

	//Enemy Health Bar
	enemyHealthBarBack.set_position(gef::Vector4(700.0f, 40.0f, -0.99f));
	enemyHealthBarBack.set_height(20.0f);
	enemyHealthBarBack.set_width(400.0f);
	enemyHealthBarBack.set_colour(0xFF000000);

	enemyHealthBar.set_position(gef::Vector4(700.0f, 40.0f, -0.99f));
	enemyHealthBar.set_height(20.0f);
	enemyHealthBar.set_width(400.0f);
	enemyHealthBar.set_colour(0xFF51F542);

	//Team character 1 Health Bar
	teamOneHealthBarBack.set_position(gef::Vector4(100.0f, 400.0f, -0.99f));
	teamOneHealthBarBack.set_height(10.0f);
	teamOneHealthBarBack.set_width(150.0f);
	teamOneHealthBarBack.set_colour(0xFF000000);

	teamOneHealthBar.set_position(gef::Vector4(100.0f, 400.0f, -0.99f));
	teamOneHealthBar.set_height(10.0f);
	teamOneHealthBar.set_width(150.0f);
	teamOneHealthBar.set_colour(0xFF51F542);

	//Team Character 2 Health Bar
	teamTwoHealthBarBack.set_position(gef::Vector4(100.0f, 450.0f, -0.99f));
	teamTwoHealthBarBack.set_height(10.0f);
	teamTwoHealthBarBack.set_width(150.0f);
	teamTwoHealthBarBack.set_colour(0xFF000000);

	teamTwoHealthBar.set_position(gef::Vector4(100.0f, 450.0f, -0.99f));
	teamTwoHealthBar.set_height(10.0f);
	teamTwoHealthBar.set_width(150.0f);
	teamTwoHealthBar.set_colour(0xFF51F542);

	teamBarWidth = teamOneHealthBarBack.width();

	menuBackground.set_position(gef::Vector4(140.0f, 240.0f, -0.99f));
	menuBackground.set_height(100.0f);
	menuBackground.set_width(200.0f);
	menuBackground.set_colour(0xFF000000);

	font = new gef::Font(plat);
	font->Load("comic_sans");

	attackText = "Attack!";
	changeCards = "Swap Cards";
	playerTurn = false;
}

void UserInterface::updateUI(std::vector<TeamCharacter*> teamChars, float fps)
{
	float healthLostFraction;
	float offset;

	//Player Health Bar
	//Work out size of bar 
	healthLostFraction = (player->getCurrHealth() / (player->getMaxHealth() + player->getBuffedHealth()));
	playerHealthBar.set_width((playerHealthBarBack.width() * healthLostFraction));

	if (healthLostFraction <= 0.2f) {
		playerHealthBar.set_colour(0xFF03109c);
	}
	else {
		playerHealthBar.set_colour(0xFF51F542);
	}
	//Adjust position for whats missing
	offset = (((playerHealthBarBack.width() - playerHealthBar.width()) / 2));
	playerHealthBar.set_position((playerHealthBarBack.position().x() - offset), playerHealthBar.position().y(), playerHealthBar.position().z());

	//Enemy Health Bar
	//Work out size of bar 
	healthLostFraction = (enemy->getCurrHealth() / enemy->getMaxHealth());
	enemyHealthBar.set_width((enemyHealthBarBack.width() * healthLostFraction));

	if (healthLostFraction <= 0.2f) {
		enemyHealthBar.set_colour(0xFF03109c);
	}
	else {
		enemyHealthBar.set_colour(0xFF51F542);
	}

	//Adjust position for whats missing
	offset = (((enemyHealthBarBack.width() - enemyHealthBar.width()) / 2));
	enemyHealthBar.set_position((enemyHealthBarBack.position().x() - offset), enemyHealthBar.position().y(), enemyHealthBar.position().z());

	if (teamChars.size() > 0) {
		//Team Char 1 Health Bar
		//Work out size of bar 
		healthLostFraction = (teamChars[0]->getCurrHealth() / teamChars[0]->getMaxHealth());
		teamOneHealthBarBack.set_width(teamBarWidth);
		teamOneHealthBar.set_width((teamOneHealthBarBack.width() * healthLostFraction));

		if (healthLostFraction <= 0.2f) {
			teamOneHealthBar.set_colour(0xFF03109c);
		}
		else {
			teamOneHealthBar.set_colour(0xFF51F542);
		}

		//Adjust position for whats missing
		offset = (((teamOneHealthBarBack.width() - teamOneHealthBar.width()) / 2));
		teamOneHealthBar.set_position((teamOneHealthBarBack.position().x() - offset), teamOneHealthBar.position().y(), teamOneHealthBar.position().z());
	}
	else{

		teamOneHealthBarBack.set_width(0);
		teamOneHealthBar.set_width(0);
	}

	if (teamChars.size() > 1) {
		//Team Char 2 Health Bar
		//Work out size of bar 
		healthLostFraction = (teamChars[1]->getCurrHealth() / teamChars[1]->getMaxHealth());
		teamTwoHealthBarBack.set_width(teamBarWidth);
		teamTwoHealthBar.set_width((teamTwoHealthBarBack.width() * healthLostFraction));

		if (healthLostFraction <= 0.2f) {
			teamTwoHealthBar.set_colour(0xFF03109c);
		}
		else {
			teamTwoHealthBar.set_colour(0xFF51F542);
		}

		//Adjust position for whats missing
		offset = (((teamTwoHealthBarBack.width() - teamTwoHealthBar.width()) / 2));
		teamTwoHealthBar.set_position((teamTwoHealthBarBack.position().x() - offset), teamTwoHealthBar.position().y(), teamTwoHealthBar.position().z());
	}
	else {
		
		teamTwoHealthBar.set_width(0);
		teamTwoHealthBarBack.set_width(0);
	}


	if (playerTurn) {
		gef::SonyControllerInputManager* controllerManager = inputManager->controller_input();
		if (controllerManager)
		{
			const gef::SonyController* controller = controllerManager->GetController(0);

			if (controller->buttons_pressed() & gef_SONY_CTRL_UP) {
				playerTurnSelection = true;
			}
			if (controller->buttons_pressed() & gef_SONY_CTRL_DOWN) {
				playerTurnSelection = false;
			}
		}
	}
}

void UserInterface::renderUI(std::vector<TeamCharacter*> teamChars, gef::Platform& platform)
{
	gef::Matrix44 proj_matrix2d;

	proj_matrix2d = platform.OrthographicFrustum(0.0f, platform.width(), 0.0f, platform.height(), -1.0f, 1.0f);
	spriteRenderer->set_projection_matrix(proj_matrix2d);

	spriteRenderer->Begin(false);

	//Render Health Bars
	spriteRenderer->DrawSprite(playerHealthBarBack);
	spriteRenderer->DrawSprite(playerHealthBar);
	spriteRenderer->DrawSprite(enemyHealthBarBack);
	spriteRenderer->DrawSprite(enemyHealthBar);
	spriteRenderer->DrawSprite(teamOneHealthBarBack);
	spriteRenderer->DrawSprite(teamOneHealthBar);
	spriteRenderer->DrawSprite(teamTwoHealthBarBack);
	spriteRenderer->DrawSprite(teamTwoHealthBar);
	
	//Render Turn Choice Window
	if (playerTurn) {
		spriteRenderer->DrawSprite(menuBackground);
		
		if (font)
		{
			if (playerTurnSelection){
				font->RenderText(spriteRenderer, gef::Vector4(50.f, 200.0f, -0.99f), 1.2f, 0xFF03F7FF, gef::TJ_LEFT, attackText);
				font->RenderText(spriteRenderer, gef::Vector4(50.f, 250.0f, -0.99f), 1.0f, 0xffffffff, gef::TJ_LEFT, changeCards);
			}
			else {
				font->RenderText(spriteRenderer, gef::Vector4(50.f, 200.0f, -0.99f), 1.0f, 0xffffffff, gef::TJ_LEFT, attackText);
				font->RenderText(spriteRenderer, gef::Vector4(50.f, 250.0f, -0.99f), 1.2f, 0xFF03F7FF, gef::TJ_LEFT, changeCards);
			}
			
		}

	}
	const char * temp;

	//Render Buff Text
	if (teamChars.size() > 0) {
		if (teamChars[0]->getOffensive()) {
			font->RenderText(spriteRenderer, gef::Vector4(50.f, 50.0f, -0.99f), 1.2f, 0xFF03F7FF, gef::TJ_LEFT, teamChars[0]->getOffensiveText());
		}
		else {
			font->RenderText(spriteRenderer, gef::Vector4(50.f, 50.0f, -0.99f), 1.2f, 0xFF03F7FF, gef::TJ_LEFT, teamChars[0]->getDefensiveText());
		}
		
		font->RenderText(spriteRenderer, gef::Vector4(30.f, 360.0f, -0.99f), 1.f, teamChars[0]->getColourMaterial()->colour(), gef::TJ_LEFT, teamChars[0]->getClassText(), " Lvl. ", teamChars[0]->getLevel());
	}
	if (teamChars.size() > 1) {
		if (teamChars[1]->getOffensive()) {
			font->RenderText(spriteRenderer, gef::Vector4(50.f, 100.0f, -0.99f), 1.2f, 0xFF03F7FF, gef::TJ_LEFT, teamChars[1]->getOffensiveText());
		}
		else {
			font->RenderText(spriteRenderer, gef::Vector4(50.f, 100.0f, -0.99f), 1.2f, 0xFF03F7FF, gef::TJ_LEFT, teamChars[1]->getDefensiveText());
		}
		font->RenderText(spriteRenderer, gef::Vector4(30.f, 410.0f, -0.99f), 1.f, teamChars[1]->getColourMaterial()->colour(), gef::TJ_LEFT, teamChars[1]->getClassText(), " Lvl. ", teamChars[1]->getLevel());
	}

	spriteRenderer->End();
}

void UserInterface::playerBattleUI()
{


}
