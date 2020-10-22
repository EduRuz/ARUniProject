#include "Player.h"
#include <graphics/mesh.h>


Player::Player() :
	Character()
{
}


Player::~Player()
{
}

void Player::initPlayer(PrimitiveBuilder* primitiveBuilder, gef::Platform& platform)
{
	markerCode = 00;
	markerFound = false;
	alive = true;

	colourMaterial = new gef::Material();
	colourMaterial->set_colour(0xFF7600AD);//Purple

	//gef::Mesh *m = primitiveBuilder->CreateBoxMesh(gef::Vector4(0.5f, 0.5f, 0.5f), gef::Vector4(0.0f, 0.0f, 0.0f), &colourMaterial);
	//for (int i = 0; i < m->num_primitives(); i++)
	//	m->GetPrimitive(i)->set_material(colourMaterial);

	//set_mesh(m);

	model = new gef::Scene();
	model->ReadSceneFromFile(platform, "PlayerDragonite.scn");
	model->CreateMaterials(platform);
	sceneMesh = getFirstMesh(model, platform);

	set_mesh(sceneMesh);

	init();
	setPosition(0.0f, 0.f, 0.f);
	setScale(0.01f, 0.01f, 0.01f);
	buildTransform();

	initVariables();
}

void Player::updatePlayer(std::vector<TeamCharacter*> teamChars, float fps)
{
	update(fps);
}

void Player::initVariables()
{
	maxHealth = 150;
	shield = 50;
	currVitality = maxHealth;
	currVitality -= 50;
	currHealth = maxHealth;
	currHealth -= 50;
	healingPerRound = 10.f;
	attackVal = 25.f;
	speed = 20.f;
	markerCode = 00;

	setUpCurrentVals();
}

void Player::resetBuffs()
{

	if (buffedAttackVal != 0.f) {
	
		currAttackVal -= buffedAttackVal;
		buffedAttackVal = 0.f;
	}
	
	if (buffedHealingPerRound != 0) {

		currHealingPerRound -= buffedHealingPerRound;
		buffedHealingPerRound = 0;
	}

	if (buffedHealth != 0) {
		currHealth -= buffedHealth;
		buffedHealth = 0;
	}

	if (buffedShield != 0) {
		currShield -= buffedShield;
		buffedShield = 0;
	}

	if (buffedSpeed != 0) {
		currSpeed -= buffedSpeed;
		buffedSpeed = 0;	
	}
}

void Player::buffPlayer()
{

	currHealth += buffedHealth;
	currAttackVal += buffedAttackVal;
	currHealingPerRound += buffedHealingPerRound;
	currShield += buffedShield;
	currSpeed += buffedSpeed;
}
