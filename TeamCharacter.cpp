#include "TeamCharacter.h"
#include <graphics/mesh_instance.h>
#include <graphics/mesh.h>
#include <graphics/scene.h>


TeamCharacter::TeamCharacter() :
	Character()
{
}


TeamCharacter::~TeamCharacter()
{
}

void TeamCharacter::activateOffensiveAbilty()
{
	switch (characterClass)
	{
	case CharacterClass::PRIEST:
		//Increases shields by a large amount
		player->setBuffedShield(50);
		
		break;

	case CharacterClass::RANGER:
		//Increases Attack by a medium amount
		player->setBuffedAttack(10);
		break;

	case CharacterClass::WARRIOR:
		//Increases Attack by a small amount
		player->setBuffedAttack(5);
		break;

	case CharacterClass::PALADIN:
		//Increases Speed by a small amount
		player->setBuffedSpeed(5);
		break;

	case CharacterClass::SHAMAN:
		//Lowers Total Health by a small amount but increases Attack by a large amount
		player->setBuffedHealth(-20);
		player->setBuffedAttack(15);
		break;
	}

	offensive = true;
}

void TeamCharacter::activateDefensiveAbility()
{
	switch (characterClass)
	{
	case CharacterClass::PRIEST:
		//Increases HealingPerRound by a large amount
		player->setBuffedHealing(15);
		break;

	case CharacterClass::RANGER:
		//Increases Speed by a medium amount
		player->setBuffedSpeed(10);
		break;

	case CharacterClass::WARRIOR:
		//Increases Total Health by a medium amount
		player->setBuffedHealth(35);
		break;

	case CharacterClass::PALADIN:
		//Increases Shield by a medium amount
		player->setBuffedShield(35);
		break;

	case CharacterClass::SHAMAN:
		//Lowers HealingPerRound by a small amount but increases Speed by a large amount
		player->setBuffedHealing(-5);
		player->setBuffedSpeed(15);
		break;
	}

	offensive = false;
}

void TeamCharacter::initObject(PrimitiveBuilder* primitiveBuilder, gef::Vector4 scale)
{
	markerFound = false;
	alive = true;
	offensive = true;
	setUpCurrentVals();

	gef::Mesh *m = primitiveBuilder->CreateBoxMesh(gef::Vector4(0.5f, 0.5f, 0.5f), gef::Vector4(0.0f, 0.0f, 0.0f), &colourMaterial);

	for (int i = 0; i < m->num_primitives(); i++)
		m->GetPrimitive(i)->set_material(colourMaterial);

	set_mesh(m);

	init();
	setPosition(0.0f, 0.f, 0.f);
	setScale(scale.x(), scale.y(), scale.z());
	buildTransform();
}

void TeamCharacter::initPriest(Player* player_, PrimitiveBuilder* primitiveBuilder, gef::Platform& platform)
{
	player = player_;

	model = new gef::Scene();
	model->ReadSceneFromFile(platform, "PriestTogetic.scn");
	model->CreateMaterials(platform);
	sceneMesh = getFirstMesh(model, platform);

	set_mesh(sceneMesh);

	colourMaterial = new gef::Material();//White
	colourMaterial->set_colour(0xFFFFFFFF);

	characterClass = CharacterClass::PRIEST;
	maxHealth = 100.f;
	shield = 0.f;
	healingPerRound = 20.f;
	attackVal = 10.f;
	speed = 10.f;
	markerCode = 01;
	offensiveText = "Shield +++";
	defensiveText = "Healing +++";
	classText = "Priest";

	markerFound = false;
	alive = true;
	offensive = true;
	setUpCurrentVals();

	init();
	setPosition(0.0f, 0.f, 0.f);
	setScale(0.01f, 0.01f, 0.01f);
	buildTransform();

	//initObject(primitiveBuilder, gef::Vector4(0.045f, 0.045f, 0.10f));

	//currHealth -= 90.f;
}

void TeamCharacter::initRanger(Player* player_, PrimitiveBuilder* primitiveBuilder, gef::Platform& platform)
{
	player = player_;

	model = new gef::Scene();
	model->ReadSceneFromFile(platform, "RangerZapdos.scn");
	model->CreateMaterials(platform);
	sceneMesh = getFirstMesh(model, platform);

	set_mesh(sceneMesh);

	colourMaterial = new gef::Material();
	colourMaterial->set_colour(0xFF51F542);//Green

	characterClass = CharacterClass::RANGER;
	maxHealth = 120.f;
	shield = 0.f;
	healingPerRound = 10.f;
	attackVal = 25.f;
	speed = 25.f;
	markerCode = 02;
	offensiveText = "Attack ++";
	defensiveText = "Speed ++";
	classText = "Ranger";

	markerFound = false;
	alive = true;
	offensive = true;
	setUpCurrentVals();

	init();
	setPosition(0.0f, 0.f, 0.f);
	setScale(0.01f, 0.01f, 0.01f);
	buildTransform();

	//initObject(primitiveBuilder, gef::Vector4(0.055f, 0.065f, 0.050f));

	//currHealth -= 100.f;
}

void TeamCharacter::initWarrior(Player* player_, PrimitiveBuilder* primitiveBuilder, gef::Platform& platform)
{
	player = player_;

	colourMaterial = new gef::Material();
	colourMaterial->set_colour(0xFF03109c);//Dark Red FF781C00

	model = new gef::Scene();
	model->ReadSceneFromFile(platform, "WarriorScizor.scn");
	model->CreateMaterials(platform);
	sceneMesh = getFirstMesh(model, platform);

	set_mesh(sceneMesh);

	characterClass = CharacterClass::WARRIOR;
	maxHealth = 160.f;
	shield = 40.f;
	healingPerRound = 5.f;
	attackVal = 20.f;
	speed = 5.f;
	markerCode = 03;
	offensiveText = "Attack +";
	defensiveText = "Health ++";
	classText = "Warrior";

	markerFound = false;
	alive = true;
	offensive = true;
	setUpCurrentVals();

	init();
	setPosition(0.0f, 0.f, 0.f);
	setScale(0.01f, 0.01f, 0.01f);
	buildTransform();

	//initObject(primitiveBuilder, gef::Vector4(0.040f, 0.060f, 0.040f));
}

void TeamCharacter::initPaladin(Player* player_, PrimitiveBuilder* primitiveBuilder, gef::Platform& platform)
{
	player = player_;

	colourMaterial = new gef::Material();
	colourMaterial->set_colour(0xFF03F7FF);//Yellow

	model = new gef::Scene();
	model->ReadSceneFromFile(platform, "PaladinMeganium.scn");
	model->CreateMaterials(platform);
	sceneMesh = getFirstMesh(model, platform);

	set_mesh(sceneMesh);

	characterClass = CharacterClass::PALADIN;
	maxHealth = 120.f;
	shield = 80.f;
	healingPerRound = 15.f;
	attackVal = 15.f;
	speed = 15.f;	
	markerCode = 04;

	offensiveText = "Speed +";
	defensiveText = "Shields ++";
	classText = "Paladin";

	markerFound = false;
	alive = true;
	offensive = true;
	setUpCurrentVals();

	init();
	setPosition(0.0f, 0.f, 0.f);
	setScale(0.01f, 0.01f, 0.01f);
	buildTransform();

	//initObject(primitiveBuilder, gef::Vector4(0.045f, 0.065f, 0.045f));

	//currHealth -= 100.f;
}

void TeamCharacter::initShaman(Player* player_, PrimitiveBuilder* primitiveBuilder, gef::Platform& platform)
{
	player = player_;

	colourMaterial = new gef::Material();
	colourMaterial->set_colour(0xFFFF030F);//Blue 0xFF3B96F7

	model = new gef::Scene();
	model->ReadSceneFromFile(platform, "ShamanLugia.scn");
	model->CreateMaterials(platform);
	sceneMesh = getFirstMesh(model, platform);

	set_mesh(sceneMesh);

	characterClass = CharacterClass::SHAMAN;
	maxHealth = 60.f;
	shield = 40.f;
	healingPerRound = 0.f;
	attackVal = 35.f;
	speed = 20.f;
	markerCode = 05;

	offensiveText = "Attack +++ health -";
	defensiveText = "Speed +++ healing -";
	classText = "Shaman";

	markerFound = false;
	alive = true;
	offensive = true;
	setUpCurrentVals();

	init();
	setPosition(0.0f, 0.f, 0.f);
	setScale(0.01f, 0.01f, 0.01f);
	buildTransform();

	//initObject(primitiveBuilder, gef::Vector4(0.060f, 0.065f, 0.050f));
}
