#include "Character.h"



Character::Character() :
	GameObject()
{
}


Character::~Character()
{
}

void Character::sharedUpdate()
{

}

void Character::cleanUp()
{
	delete colourMaterial;
	colourMaterial = NULL;

	delete model;
	model = NULL;

	delete mesh_;
	mesh_ = NULL;
}

void Character::setMarkerFound(bool flag)
{
	markerFound = flag;
}

void Character::setUpCurrentVals()
{
	currAttackVal = attackVal;
	currHealingPerRound = healingPerRound;
	currHealth = maxHealth;
	currShield = shield;
	currSpeed = speed;
}

gef::Mesh * Character::getFirstMesh(gef::Scene * scene, gef::Platform& platform)
{
	gef::Mesh* mesh = NULL;

	if (scene)
	{
		// now check to see if there is any mesh data in the file, if so lets create a mesh from it
		if (scene->mesh_data.size() > 0)
			mesh = scene->CreateMesh(platform, scene->mesh_data.front());
	}

	return mesh;
}
