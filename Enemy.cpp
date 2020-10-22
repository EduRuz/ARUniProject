#include "Enemy.h"
#include <graphics/mesh.h>


Enemy::Enemy() : 
	Character()
{
}


Enemy::~Enemy()
{
}

void Enemy::initFirstBoss(PrimitiveBuilder* primitiveBuilder, gef::Platform& platform)
{
	colourMaterial = new gef::Material();
	colourMaterial->set_colour(0xFF000000);//Black

	//gef::Mesh *m = primitiveBuilder->CreateBoxMesh(gef::Vector4(0.5f, 0.5f, 0.5f), gef::Vector4(0.0f, 0.0f, 0.0f), &colourMaterial);
	//for (int i = 0; i < m->num_primitives(); i++)
	//	m->GetPrimitive(i)->set_material(colourMaterial);

	//set_mesh(m);

	model = new gef::Scene();
	model->ReadSceneFromFile(platform, "EnemyMewtwo.scn");
	model->CreateMaterials(platform);
	sceneMesh = getFirstMesh(model, platform);

	set_mesh(sceneMesh);

	init();
	setPosition(0.0f, 0.f, 0.f);
	setScale(0.05f, 0.05f, 0.05f);
	buildTransform();

	initBossVariables();
}

void Enemy::initBossVariables()
{
	maxHealth = 800;
	shield = 200;
	attackVal = 20;
	healingPerRound = 0;
	speed = 20;


	setUpCurrentVals();
	//currVitality -= 700;
}
